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
#region Using directives

using System;
using System.Drawing;
using System.Collections;
using System.Windows.Forms;

using System.Xml;
using Microsoft.WindowsMobile.Configuration;

#endregion

namespace SecurityViewer
{
    /// <summary>
    /// Summary description for form.
    /// </summary>
    public class Form1 : System.Windows.Forms.Form
    {
        private TreeView treeView1;
        private MenuItem menuItem1;
        /// <summary>
        /// Main menu for the form.
        /// </summary>
        private System.Windows.Forms.MainMenu mainMenu1;

        public Form1()
        {
            InitializeComponent();
        }

        /// <summary>
        /// Clean up any resources being used.
        /// </summary>
        protected override void Dispose(bool disposing)
        {
            base.Dispose(disposing);
        }

        #region Windows Form Designer generated code
        /// <summary>
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            this.mainMenu1 = new System.Windows.Forms.MainMenu();
            this.treeView1 = new System.Windows.Forms.TreeView();
            this.menuItem1 = new System.Windows.Forms.MenuItem();
            // 
            // mainMenu1
            // 
            this.mainMenu1.MenuItems.Add(this.menuItem1);
            // 
            // treeView1
            // 
            this.treeView1.Indent = 20;
            this.treeView1.Location = new System.Drawing.Point(0, 0);
            this.treeView1.Size = new System.Drawing.Size(176, 180);
            // 
            // menuItem1
            // 
            this.menuItem1.Text = "Quit";
            this.menuItem1.Click += new System.EventHandler(this.menuItem1_Click);
            // 
            // Form1
            // 
            this.ClientSize = new System.Drawing.Size(176, 180);
            this.Controls.Add(this.treeView1);
            this.Menu = this.mainMenu1;
            this.Text = "Form1";
            this.Load += new System.EventHandler(this.Form1_Load);

        }

        #endregion

        /// <summary>
        /// The main entry point for the application.
        /// </summary>
        static void Main()
        {
            Application.Run(new Form1());
        }

        private void menuItem1_Click(object sender, EventArgs e)
        {
            Application.Exit();
        }

        private void Form1_Load(object sender, System.EventArgs e)
        {
            treeView1.Size = this.Size;

            // Read the certificates that are installed on the device
            XmlDocument xmlCerts = new XmlDocument();
            xmlCerts.LoadXml("<wap-provisioningdoc><characteristic type=\"CertificateStore\"><characteristic-query type=\"Privileged Execution Trust Authorities\"/><characteristic-query type=\"Unprivileged Execution Trust Authorities\"/> <characteristic-query type=\"SPC\"/> <characteristic-query type=\"MY\"/> <characteristic-query type=\"CA\"/> </characteristic> </wap-provisioningdoc>");
            XmlDocument domCerts = ConfigurationManager.ProcessConfiguration(xmlCerts, false);

            domCerts.Save(@"\My Documents\Certificates.xml");

            // Read all the security policies
            XmlDocument xmlPolicy = new XmlDocument();
            xmlPolicy.LoadXml("<wap-provisioningdoc><characteristic type=\"SecurityPolicy\">		<parm-query name=\"2\"/>		<parm-query name=\"4097\"/>		<parm-query name=\"4101\"/>			<parm-query name=\"4103\"/>		<parm-query name=\"4104\"/>		<parm-query name=\"4105\"/>		<parm-query name=\"4107\"/>		<parm-query name=\"4108\"/> 		<parm-query name=\"4109\"/>		<parm-query name=\"4110\"/>		<parm-query name=\"4111\"/>		<parm-query name=\"4112\"/>		<parm-query name=\"4113\"/>		<parm-query name=\"4119\"/>		<parm-query name=\"4120\"/>		<parm-query name=\"4121\"/>				<parm-query name=\"4129\"/>	<parm-query name=\"4102\"/>	<parm-query name=\"4122\"/>	<parm-query name=\"4123\"/> </characteristic></wap-provisioningdoc>");
            XmlDocument domPolicy = ConfigurationManager.ProcessConfiguration(xmlPolicy, false);

            domPolicy.Save(@"\My Documents\Policies.xml");

            // Read the subset of the security policies that define the Security Configuration
            XmlDocument xmlConfig = new XmlDocument();
            xmlConfig.LoadXml("<wap-provisioningdoc><characteristic type=\"SecurityPolicy\"> <parm-query name=\"4102\"/>	<parm-query name=\"4122\"/>	<parm-query name=\"4123\"/> </characteristic></wap-provisioningdoc>");
            XmlDocument domConfig = ConfigurationManager.ProcessConfiguration(xmlConfig, false);

            XmlNodeList listParms = domConfig.FirstChild.FirstChild.ChildNodes;
            int unsignedApps = Convert.ToInt32(listParms[0].Attributes["value"].Value);
            int prompt       = Convert.ToInt32(listParms[1].Attributes["value"].Value);
            int tier         = Convert.ToInt32(listParms[2].Attributes["value"].Value);

            string securityConfig = "not one of the 3 predefined configurations";
            if (tier == 0 && unsignedApps == 0 && prompt == 1)
            {
                securityConfig = "Third-Party-Signed or Locked";
            }
            if (tier == 0 && unsignedApps == 1 && prompt == 0)
            {
                securityConfig = "Two-Tier-Prompt";
            }
            if (tier == 0 && unsignedApps == 1 && prompt == 1)
            {
                securityConfig = "Two-Tier-Prompt, except prompt mode is off";
            }
            if (tier == 1 && unsignedApps == 1 && prompt == 0)
            {
                securityConfig = "One-Tier-Prompt";
            }
            if (tier == 1 && unsignedApps == 1 && prompt == 1)
            {
                securityConfig = "One-Tier-Prompt, except prompt mode is off";
            }
            MessageBox.Show("The security configuration is " + securityConfig + ".");


            try
            {
                treeView1.Nodes.Clear();

                treeView1.Nodes.Add(new TreeNode(domCerts.DocumentElement.Name));
                TreeNode tNode = treeView1.Nodes[0];
                // Populate the TreeView with the DOM nodes for the certificates.
                AddNode(domCerts.DocumentElement, tNode);


                treeView1.Nodes.Add(new TreeNode(domPolicy.DocumentElement.Name));
                tNode = treeView1.Nodes[1];
                // Populate the TreeView with the DOM nodes for the security policy.
                AddNode(domPolicy.DocumentElement, tNode);

                treeView1.ExpandAll();
            }
            catch (XmlException xmlEx)
            {
                MessageBox.Show(xmlEx.Message);
            }
            catch (Exception ex)
            {
                MessageBox.Show(ex.Message);
            }
        }


        private void AddNode(XmlNode inXmlNode, TreeNode inTreeNode)
        {
            XmlNode xNode;
            TreeNode tNode;
            XmlNodeList nodeList;
            int i;

            // Loop through the XML nodes until the leaf is reached.
            // Add the nodes to the TreeView during the looping process.
            if (inXmlNode.HasChildNodes)
            {
                nodeList = inXmlNode.ChildNodes;
                for (i = 0; i <= nodeList.Count - 1; i++)
                {
                    xNode = inXmlNode.ChildNodes[i];
                    inTreeNode.Nodes.Add(new TreeNode(xNode.Name));
                    tNode = inTreeNode.Nodes[i];
                    AddNode(xNode, tNode);
                }
            }
            else
            {
                // Here you need to pull the data from the XmlNode based on the
                // type of node, whether attribute values are required, and so forth.
                inTreeNode.Text = (inXmlNode.OuterXml).Trim();
            }
        }   

    }
}

