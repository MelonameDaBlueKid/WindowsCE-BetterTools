Code Sample Name: MediaPlayerHomePlugin

Feature Area: Windows Media Player

Description: 
    This sample implements a homescreen plugin for the Smartphone. This plugin allows 
    the user to view information about the current media item playing in Windows Media
    Player, and provides controls to pause or restart playback, to move to the next 
    media item in the current playlist, and to move to the previous media item in the 
    current playlist.

    In order to interact with Windows Media Player in this way, a custom Windows Media 
    Player plugin is also required. This sample therefore implements a Windows Media 
    Player UI Plugin as well.

Usage: 
    Build all the projects in the solution from Visual Studio 2005, including the
    Smart Device CAB Project called WMPHomePlugin. This project will generate a CAB that
    you then can run from your device.

    Note: If you have not installed the SDKSamplePrivDeveloper certificate, you 
    will need to do that so that your dll and cab projects are signed correctly.  

    To install the certificate from the windows desktop:
    1. Click Start
    2. Click Run
    3. Type in the path to SDKSamplePrivDeveloper.pfx.  (This file will be where 
       you installed the Smartphone SDK under the Tools directory)
    4. Click OK
       (The Certificate Import Wizard should appear)
    5. Click Next
       (The path to the certificate should be filled in for the File name)
    6. Click Next
    7. Click Next (you do not need a password)
    8. Click Next (you want the default options here: Automatically select the 
       certificate store based on the type of certificate)
    9. Click Finish

Relevant APIs/Associated Help Topics: 

    Building a Home-Screen plugin
    IHomePlugin
    IPersistStream
    IHomePluginEnvironment2
    IWMPPluginUI
    IWMPEvents

Assumptions:
    Test Certs are installed on desktop machine to properly sign the cab and dll.

Requirements: 
    Visual Studio 2005, 
    Windows Mobile 6 Standard SDK,
    Activesync 4.5


Additional Technical Information:


1. Display Attributes in the XML File

    In order to be a well-behaved plugin, a homescreen plugin should parse any 
    attributes in the layout XML file that apply to it. In particular, it should 
    pay attention to the following attributes in the <default> node:

        font-face                                           Name of font for any text that is drawn 
        font-size                                           Size of font (see sample code for how this is interpreted) 
        font-weight                                         Weight of font 
        font-style                                          Style of font, e.g., italic 
        padding-left, padding-right, padding-top            Padding metrics, in pixels (relative to the plugin’s assigned rectangle) 
        fgcolor                                             Name of foreground (text) color to use 
        bgcolor                                             Name of background color to use, or “transparent” 
        b-border-color                                      Color of bottom border 
        b-border-width                                      Width of bottom border line 

    The plugin should also respect attributes in the <format state="selected">
    child of the <default> node. Any attributes here override the attributes 
    specified in the <default> node when the plugin is in the selected state.

    Additionally, the <plugin> node itself may specify additional attributes, 
    and it may contain a <background> child node containing additional attributes, 
    which in turn may contain a <format state="selected"> node with yet more 
    attributes. The override behavior here is complicated.

    This sample contains a class named CDisplayAttributes which serves to encapsulate 
    a set of attributes. The Initialize method of this class reads a collection of 
    attributes from the <default> and <plugin> nodes (IXMLDOMNode interface pointers),
    and stores these attribute values internally, along with a set of bit flags 
    indicating which attributes were found. The SaveToStream method of this class will 
    save all attribute values (and the bit flags) to an IStream, while the 
    LoadFromStream method loads attribute values (and bit flags) from an IStream. 
    The latter two methods are a great aid when implementing the IPersistStream::Load 
    and IPersistStream::Save methods in the plugin itself.

    See the code for examples of how the override behavior is handled, and how 
    default values are returned if necessary.

    If the CDisplayAttributes class doesn’t manage the set of attributes you’re 
    interested in, it should be relatively easy to make changes to this class.

2. HomeScreen Plugin Lifecycle

    A homescreen plugin is created by HOME.EXE calling CoCreateInstance with 
    the plugin’s CLSID. Thereafter, the plugin may be initialized in one of 
    two ways:

        by calling its IHomePlugin::Initialize method;
        -OR- 
        by calling its IPersistStream::Load method 
 

    You should not assume which method will be used. HOME.EXE may choose to 
    create an instance of your plugin, call its IHomePlugin::Initialize method,
    and then call its IPersistStream::Save method. It may then Release your 
    plugin and later on create another instance, which it will initialize by 
    calling its IPersistStream::Load method (using the data saved earlier).

    Therefore, all member data initialized by your Initialize method must be 
    saved to the stream in your Save method, and must be initialized properly 
    from the stream by your Load method. For example, assume your plugin has 
    three data members: A, B and C (all of type int). Your constructor sets 
    each to 0. In your Initialize method, you end up setting A=1, B=2 and C=3. 
    In your Save method, you save only B and C, neglecting A. When another 
    instance of your plugin is created, and its Load method is called, only B 
    and C will be restored properly (to 2 and 3) – A will remain 0 as set by 
    the constructor, when it should be 1.

    Furthermore, do not assume that your DLL will remain loaded (this is a general 
    COM rule, but it’s particularly relevant here). HOME.EXE may choose to create 
    an instance of your plugin, save its data to an IStream and then Release that 
    instance, thus unloading your DLL. When HOME.EXE next creates an instance of 
    your plugin (and calls its Load method), any data you had saved globally in 
    your DLL will again contain default values, since the DLL instance itself is new.

    Finally, do not assume that the HOME.EXE process itself will remain intact. 
    For example, if you create a kernel object (such as an event or mutex), do not 
    serialize its handle to the stream in your IPersistStream::Save method, since that 
    object will be destroyed if HOME.EXE terminates. If a subsequent HOME.EXE process 
    creates an instance of your plugin, and asks you to load your data (via 
    IPersistStream::Load), the handle value you retrieve will be invalid.


3. The Windows Media Player UI Plugin

    The homescreen plugin is only half the story – in order to control Windows Media 
    Player, we need a Windows Media Player UI plugin as well.

    Implementing a “background” Media Player UI plugin (which is all that Windows 
    Media Player Mobile Edition supports) is relatively simple, requiring only that 
    you implement the IWMPPluginUI interface, which contains only 7 methods, most of 
    which don’t require any interesting implementation anyway.

    In order to find out about “events”, such as state changes in Windows Media Player,
    you must also implement the IWMPEvents interface, which is unfortunately quite large.
    To get Windows Media Player to inform you of these events (that is, to call the methods
    of your interface implementation), you must “register” with its IConnectionPoint 
    implementation, as demonstrated in the Media Player plugin sample.

4. Communication Between the Media Player Plugin and the HomeScreen Plugin

    In order for the homescreen plugin to control Windows Media Player, it must obviously 
    have a communication channel open with the Media Player plugin. This amounts to an 
    interprocess communication (IPC) problem, and there are many well-documented ways to 
    solve this.

    One very important point regarding IPC on a Smartphone: a thread should never poll 
    for information. Polling (that is, looping continuously looking for a message or update) 
    is not only wasteful of CPU time, but will drain the battery on a Smartphone, as the 
    Smartphone is unable to effectively enter a low-power state. Windows offers plenty of 
    synchronization objects that allow a thread to enter the wait state until the object 
    becomes “signaled”, thereby avoiding polling. 

    HomeScreen Plugin -> Media Player Plugin

    The Media Player plugin simply creates a hidden window. Since Windows Media Player 
    runs a standard message pump, the window procedure defined in the Media Player 
    plugin will receive any messages posted to it by the homescreen plugin (or 
    any other source, for that matter). The homescreen plugin therefore looks for this 
    hidden window (using FindWindow and passing the class name and window name) and then 
    posts a simple custom message. See the file COMMUNICATION.H in the COMMON folder for 
    a list of the messages used. Note that using window messages in this manner avoids 
    polling, since the GetMessage API will place the calling thread in the wait state 
    if there are no messages available.

    Media Player Plugin -> HomeScreen Plugin

    The homescreen plugin creates a message queue object and uses an auxiliary thread to 
    look for messages arriving in this message queue. The message queue object is named, 
    so the Media Player plugin can find it by name in order to write update information 
    to the queue. Since a message queue HANDLE can be passed to WaitForObject (or any of 
    the other similar APIs, such as WaitForMultipleObjects), using a message queue also 
    avoids polling. If you look at the sample code, you’ll see that the auxiliary thread 
    enters a wait state (by calling WaitForMultipleObjects) until a message actually arrives. 
    Thus, the auxiliary thread spends much of its time “sleeping”.

    Note that we could have used either technique for both “channels”. In general, using a 
    hidden window that receives custom messages is the simpler approach, though it only works 
    if the thread that creates that window is running a “message pump” (GetMessage/DispatchMessage).
    Typically, this means the thread is a “UI thread”. The other disadvantage of this approach 
    is that it’s difficult to convey large blocks of data. Simply passing a pointer in (for 
    example) the LPARAM of a custom message obviously doesn’t work, since the pointer has no 
    meaning to the other process. The system-defined WM_COPYDATA message is capable of copying 
    an arbitrary-sized block of data, though, so that may be an option. 


5. “Deferred” Updates

    Because the notifications that Media Player sends to the Media Player Plugin are fairly 
    fine-grained, and because we don’t want to miss any notifications, the Media Player plugin 
    ends up sending quite a few notifications to the HomeScreen Plugin.

    A naïve approach for the HomeScreen Plugin would be to simply invalidate itself (via 
    IHomePluginEnvironment::InvalidatePlugin) on every notification. Unfortunately, this can cause 
    the state of the buttons to change rapidly, resulting in ‘flashing’ on the display. For 
    example, when the HomeScreen Plugin sends a notification to the Media Player Plugin asking 
    it to “go to next track”, the Media Player Plugin may end up sending a dozen or more 
    notifications back, including “playing” and “paused” notifications.

    Therefore, the HomeScreen Plugin adopts the following approach:

        It maintains a flag (m_fTimerSet) to determine if it’s set the single-shot timer or not (see 
        following points).
        
        When it receives a notification from Media Player, it first checks the flag 
        (m_fTimerSet) to see if it’s already set a single-shot timer. If not, it does 
        so and sets the flag to TRUE. The timer is set to go off in CMSEC_INVALIDATE_TIMER 
        milliseconds, which is a constant set in the source file (HomePlugin.cpp). 

        If the call to IHomePluginEnvironment::SetSingleShotTimer fails for some reason, the 
        HomeScreen Plugin falls back to the behavior of simply invalidating itself. 

        When the HomeScreen Plugin’s OnEvent method receives a PE_TIMER message, it 
        invalidates itself. 

    Thus, the HomeScreen Plugin doesn’t respond to every notification received from the 
    Media Player Plugin; it essentially responds to them in “batches”.

    If you set the timer value (CMSEC_INVALIDATE_TIMER) too low, you will reintroduce 
    the ‘flashing’ behavior. If you set the timer value too high, the display updates 
    will appear sluggish. Therefore, it’s important to use a timer value that works well 
    for the particular device you’re targeting.

6. Media Player Settings

    Windows Media Player has a setting that causes it to go into the “pause” state when
    it is no longer the foreground application. If this setting is turned on, the 
    homescreen plugin will be rendered almost useless, as every time the user clicks the 
    action button, the media will play briefly and then pause again.

    Therefore, you need to make sure this feature is set up correctly. The following 
    registry key controls this feature:

    HKEY_CURRENT_USER\SOFTWARE\Microsoft\MediaPlayer\Preferences
        "PlayInBackground" : DWORD
        Value:  0x00000001 (1)
        Description: Set to a nonzero value to continue playing when the Player is in the background.
                     Set to zero to pause playback when the Player is in the background.
 
    You should ensure that this registry value is 1. Be aware that the user can change 
    this value via the Media Player UI.

7. Hi-DPI Devices

    For a hi-dpi device, replace the Buttons.bmp file located in the HomePlugin directory 
    with the Buttons.bmp file located in the HomePlugin\HiDPI directory. You will also need 
    to update the file HomePlugin\HomePlugin.cpp: change the defined values of CX_BUTTON 
    and CY_BUTTON from 20 to 27.

** For more information about this code sample, please see the Windows Mobile SDK help system. **
