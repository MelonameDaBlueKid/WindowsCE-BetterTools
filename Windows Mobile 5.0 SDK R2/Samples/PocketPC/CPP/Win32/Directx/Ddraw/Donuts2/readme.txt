Code Sample Name:  Donuts2

Feature Area: Direct Draw

Description: 
    This simple game shows how to combine DirectDraw and waveform audio. 
    Although it demonstrates other DirectX components, it is 
    primarily intended to show how to animate multiple sprites.

    This game demonstrates many of the features of DirectDraw. It takes 
    advantage of hardware acceleration if it is supported by the driver. 

Relevant APIs: 
    DirectDraw

Usage:
    Load the project from Visual Studio 2005, and build and deploy normally.

    User's Guide:
    
      Input is from the keyboard. No other input device is supported.
      The commands are listed on the opening screen. All numbers must be entered 
      from the numeric keypad.

      Button          Command

      Left            Turn left

      Right           Turn right

      Up              Accelerate forward

      Down            Accelerate backward

      App Button 1    Stop

      App Button 2    Shield

      Action          Fire, Start game

      Talk button     Turn audio on/off

      End button      Quit

      Volume Up       Toggle trailing afterimage effect on/off

      Volume Down     Toggle frame rate display on/off


      The game uses the following command line switches, which are case-sensitive:

      e    Use software emulation, not hardware acceleration

      t    Test mode, no input required

      x    Stress mode. Never stop if you can help it

      S    Turn sound off/on


Assumptions: 
    The device supports direct draw.

Requirements: 
    Visual Studio 2005, 
    Windows Mobile 5.0 Pocket PC SDK
    ActiveSync 4.0.

    The program requires less than 1 MB of video RAM. 

** For more information about this code sample, 
please see the Windows Mobile SDK help system. **
