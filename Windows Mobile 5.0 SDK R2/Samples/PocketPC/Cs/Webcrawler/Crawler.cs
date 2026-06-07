//
// Copyright (c) Microsoft Corporation.  All rights reserved.
//
//
// Use of this source code is subject to the terms of the Microsoft end-user
// license agreement (EULA) under which you licensed this SOFTWARE PRODUCT.
// If you did not accept the terms of the EULA, you are not authorized to use
// this source code. For a copy of the EULA, please see the LICENSE.RTF on your
// install media.
//
/*=====================================================================
  File:      Crawler.cs
=====================================================================*/

using System;
using System.Collections;
using System.Diagnostics;
using System.IO;
using System.Net;
using System.Text.RegularExpressions;
using System.Threading;
using System.Windows.Forms;

namespace WebCrawler
{
    /// <summary>
    /// The worker class
    /// </summary>
    public class Crawler
    {
        /// <summary>
        /// Have we been asked to stop?
        /// </summary>
        private bool StopNow = true;
        
        /// <summary>
        /// The link we will use to start our crawl
        /// </summary>
        private string StartingPage = "";
        
        /// <summary>
        /// Event(s)
        /// </summary>
        public delegate void CurrentPage(string currentPage);
        public event CurrentPage CurrentPageEvent;
        public EventHandler PageFoundEvent;
        public EventHandler CrawlFinishedEvent;
        
        /// <summary>
        /// Constructor
        /// </summary>
        /// <param name="startingPage">
        /// The link we will use to start our crawl
        /// </param>
        /// <param name="noProxy">
        /// Disable crawling through an HTTP proxy server
        /// </param>
        public Crawler(string startingPage,
                    bool noProxy)
        {
            this.StartingPage = startingPage;
            
            if(noProxy)
            {
                // disable the proxy
                GlobalProxySelection.Select = new WebProxy();
            }
            else
            {
                // use the system's default proxy
                GlobalProxySelection.Select = WebProxy.GetDefaultProxy();
            }
        }
        
        /// <summary>
        /// Start the crawl
        /// </summary>
        public void Start()
        {
            lock(this)
            {
                this.StopNow = false;
            }
            new Thread(new ThreadStart(Crawl)).Start();
        }
        
        /// <summary>
        /// Stop the crawl
        /// </summary>
        public void Stop()
        {
            lock(this)
            {
                this.StopNow = true;
            }
        }
        
        /// <summary>
        /// Does the link point to HTML data?
        /// </summary>
        /// <param name="pageAddress">
        /// The link we are checking
        /// </param>
        /// <param name="status">
        /// The status code returned by the connection attempt
        /// </param>
        /// <returns>
        /// True if the link points to an HTML page, false otherwise
        /// </returns>
        private bool PageIsHtml(string pageAddress,
                                out HttpStatusCode status)
        {
            bool isHtml = false;
            const string TypeHTML = "text/html";
            
            status = (HttpStatusCode)(-2);  // not html
            
            try
            {
                // create the web request
                HttpWebRequest req = (HttpWebRequest)WebRequest.Create(pageAddress);
                
                //  get headers only
                req.Method = "HEAD";
                
                // make the connection
                HttpWebResponse resp = (HttpWebResponse)req.GetResponse();

                // read the headers
                WebHeaderCollection headers = resp.Headers;
                
                // check the content type
                string contentType = headers["Content-type"];
                if(contentType != null)
                {
                    contentType = contentType.ToLower();
                    if(contentType.Equals(TypeHTML))
                    {
                        isHtml = true;
                    }
                }

                // get the status code (should be 200)
                status = resp.StatusCode;
                
                // close the connection
                resp.Close();
            }
            catch(WebException e)
            {
                string str = string.Format("Caught WebException: {0}", e.Status.ToString());;
                
                HttpWebResponse resp = (HttpWebResponse)e.Response;
                if(null != resp)
                {
                    // get the failure code from the response
                    status = resp.StatusCode;
                    str = string.Format("{0} ({1})", str, status);
                    
                    // close the response
                    resp.Close();
                }
                else
                {
                    // generic connection error
                    status = (HttpStatusCode)(-1);
                }
                
                // update the ui so we can know what went wrong
                if(CurrentPageEvent != null)
                {
                    CurrentPageEvent(str);
                }
            }
            catch(NotSupportedException)
            { /* mailto or other reference that WebRequest.Create does not support */}
            
            // done
            return isHtml;
        }
        
        /// <summary>
        /// Read the specified web page's data
        /// </summary>
        /// <param name="pageUri">
        /// Uri object pointing to the desired page
        /// </param>
        /// <param name="pageData">
        /// The data downloaded from the provided Uri
        /// </param>
        /// <returns>
        /// The status code returned by the connection attempt
        /// </returns>
        private HttpStatusCode GetPageData(ref Uri pageUri,
                                        out string pageData)
        {
            HttpStatusCode status = (HttpStatusCode)0;

            // initialize the out param (in case of error)
            pageData = "";
                        
            try
            {
                // create the web request
                HttpWebRequest req = (HttpWebRequest)WebRequest.Create(pageUri);
                
                // make the connect
                HttpWebResponse resp = (HttpWebResponse)req.GetResponse();
                pageUri = resp.ResponseUri;
                
                // get the page data
                StreamReader sr = new StreamReader(resp.GetResponseStream());
                pageData = sr.ReadToEnd();
                sr.Close();
                
                // get the status code (should be 200)
                status = resp.StatusCode;
                
                // close the connection
                resp.Close();
            }
            catch(WebException e)
            {
                string str = string.Format("Caught WebException: {0}", e.Status.ToString());;
                
                HttpWebResponse resp = (HttpWebResponse)e.Response;
                if(null != resp)
                {
                    // get the failure code from the response
                    status = resp.StatusCode;
                    str = string.Format("{0} ({1})", str, status);
                    
                    // close the response
                    resp.Close();
                }
                else
                {
                    // generic connection error
                    status = (HttpStatusCode)(-1);
                }
                
                // update the ui so we can know what went wrong
                if(CurrentPageEvent != null)
                {
                    CurrentPageEvent(str);
                }
            }
            
            // done
            return status;
        }                                         
        
        /// <summary>
        /// Discover the links on the specified web page
        /// </summary>
        /// <param name="pageUri">
        /// Uri object pointing to the desired page
        /// </param>
        /// <param name="pageBody">
        /// The data downloaded from the specified Uri
        /// </param>
        /// <param name="tag">
        /// The HTML tag to match
        /// </param>
        /// <param name="attribute">
        /// The HTML attribute to match
        /// </param>
        /// <param name="links">
        /// Hashtable to be used for storing discovered links
        /// </param>
        private void GetPageLinks(Uri pageUri,
                                string pageBody,
                                string tag,
                                string attribute,
                                Hashtable links)
        {
            // construct the match strings
            string tagPattern = string.Format("< *{0} +[^<>]*>", tag);
            string attributePattern = string.Format("{0} *= *([^ >])*", attribute);
            
            // get rid of line breaks and tabs (replace them with spaces)
            pageBody = Regex.Replace(pageBody, 
                                    "(\\n|\\r|\\t)", 
                                    " ");
            
            // match the html tag
            MatchCollection tagMatches = Regex.Matches(pageBody, 
                                                    tagPattern, 
                                                    RegexOptions.IgnoreCase);
            foreach(Match m in tagMatches)
            {
                if(m.Groups[0].Success)
                {
                    // now match the attribute within the matched tag
                    string tagData = m.Groups[0].Captures[0].ToString();
                    Match attributeMatch = Regex.Match(tagData, 
                                                    attributePattern, 
                                                    RegexOptions.IgnoreCase);
                    if(attributeMatch.Groups[0].Success)
                    {
                        // get rid of the quotes around the link reference
                        string linkString = attributeMatch.Groups[0].Captures[0].ToString();
                        linkString = Regex.Replace(linkString, "[ \"']","");
                        
                        // trim off the attribute, leaving only the link reference
                        linkString = linkString.Substring(attribute.Length+1);
                        
                        // add the link to our local hashtable
                        try
                        {
                            // reconstruct relative paths
                            linkString = new Uri(pageUri, linkString).AbsoluteUri; 
                        
                            // add the link
                            links.Add(linkString, new LinkInfo(linkString, (HttpStatusCode)0));

                            // ring the event handler(s) letting them know we found a new link
                            if(null != PageFoundEvent)
                            {
                                PageFoundEvent(this, EventArgs.Empty);
                            }
                        }
                        catch(IndexOutOfRangeException)
                        { /* skip the malformed uri */ }
                        catch(UriFormatException)
                        { /* skip the malformed uri */ }
                        catch(ArgumentException)
                        { /* duplicate link, skipping */ }
                    }
                }
            }

        }
        
        /// <summary>
        /// Worker thread method
        /// </summary>
        private void Crawl()
        {
            Hashtable links = null;
            
            try
            {
                // store for all the links we encounter
                //  this will keep us from walking the same link more
                //  than once
                links = new Hashtable(new CaseInsensitiveHashCodeProvider(),
                                    new CaseInsensitiveComparer());
                                                    
                // make sure the starting page has a scheme
                if(-1 == this.StartingPage.IndexOf("://"))
                {
                    // add http to the page link
                    this.StartingPage = string.Format("http://{0}", this.StartingPage);
                }
                
                // add the starting page to the links table
                links.Add(this.StartingPage, new LinkInfo(this.StartingPage, 
                                                        (HttpStatusCode)0));    // not tried yet
                while(!this.StopNow)
                {
                    // temporary storage
                    Hashtable found = new Hashtable(new CaseInsensitiveHashCodeProvider(),
                                                    new CaseInsensitiveComparer());
                                                    
                    foreach(string page in links.Keys)
                    {
                        // check to see if we have been asked to stop
                        if(this.StopNow)
                        {
                            continue;
                        }
                        
                        // ring our event handler(s) to tell them what page we are crawling
                        if(CurrentPageEvent != null)
                        {
                            CurrentPageEvent(page);
                        }
    
                        LinkInfo li = (LinkInfo)links[page];
                        // check that the page contains html text
                        try
                        {
                            if( ((HttpStatusCode)0 == li.StatusCode) &&     // we have not tried to connect
                                PageIsHtml(page, out li.StatusCode) )       // the page is html
                            {
                                // read the page
                                Uri pageUri = new Uri(page);
                                string pageData = "";
                                li.StatusCode = GetPageData(ref pageUri,
                                                            out pageData);
                                // if we successfully retrieved the page data
                                if(HttpStatusCode.OK == li.StatusCode)
                                {
                                    // <a href=
                                    GetPageLinks(pageUri,
                                                pageData,
                                                "a",
                                                "href",
                                                found);
                                    // <frame src=
                                    GetPageLinks(pageUri,
                                                pageData,
                                                "frame",
                                                "src",
                                                found);
                                    // <area href=
                                    GetPageLinks(pageUri,
                                                pageData,
                                                "area",
                                                "href",
                                                found);
                                    // <link href=
                                    GetPageLinks(pageUri,
                                                pageData,
                                                "link",
                                                "href",
                                                found);
                                }
                            }
                            else
                            { /* link not a web page */ }
                        }
                        catch(UriFormatException)
                        {
                            if(CurrentPageEvent != null)
                            {
                                CurrentPageEvent(string.Format("Unable to crawl {0} (UriFormatException)", page));
                            }
                        }
                    }
                    
                    // did we discover any new links?
                    if(0 == found.Count)
                    {
                        // nope, we're done
                        lock(this)
                        {
                            this.StopNow = true;
                        }
                        continue;
                    }
    
                    // add found links to the master list
                    foreach(string page in found.Keys)
                    {
                        if(!links.ContainsKey(page))
                        {
                            System.Diagnostics.Debug.WriteLine("Adding: " + page);
                            links.Add(page, (LinkInfo)found[page]);
                        }
                    }
                }
                
            }
            catch(OutOfMemoryException)
            {
                // we're out of memory, we need to stop
                
                // release the memory we have consumed
                links = null;
                
                lock(this)
                {
                    this.StopNow = true;
                }
                
                // ring our event handler(s) to allow the interface to 
                //  display the out of memory status
                if(null != CurrentPageEvent)
                {
                    CurrentPageEvent("Crawl halted: out of memory");
                }
                
            }
            catch(Exception e)
            {
                // something bad happened, we need to stop
                lock(this)
                {
                    this.StopNow = true;
                }
                
                // ring our event handler(s) to allow the interface to 
                //  display the exception message
                if(null != CurrentPageEvent)
                {
                    CurrentPageEvent(string.Format("Crawl halted: {0} - {1}", 
                                                e.ToString(), 
                                                e.Message));
                }
            }
        
            // ring our event handler(s) to let them know we are done
            if(null != CrawlFinishedEvent)
            {
                CrawlFinishedEvent(this, EventArgs.Empty);
            }
        }                                    
    }
}
