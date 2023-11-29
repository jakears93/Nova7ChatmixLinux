# Arctis Nova 7 Chat Mix for Linux

### Dependencies
- gcc
- if using Pipewire: pulseaudio-utils
- headsetcontrol (https://github.com/Sapd/HeadsetControl)

### Setup
- Install the needed dependencies.\
- You can run 'headsetcontrol -b' to ensure that Nova 7 headset is working with the headsetcontrol program.  This will show you the battery level of your device.
- Determine which sink you would like to have the Chat and Game mixes on with the following command: 'pacmd list-sources' or 'pactl list'.  By default, the virtual audio setup script uses 'alsa_output.usb-SteelSeries_Arctis_Nova_7-00.analog-stereo'.
- If your sink differs from the default, change replace the default used in 'virtualAudioPipewire' and 'virtualAudioPulse' with your value.
- Run the install script
- The install script will compile the mixing program and install it as a user level service.  It will also copy the script to create the virtual sinks to /usr/local/bin/virtualAudio
- Run the /usr/local/bin/virtualAudio program to create your Chat Mix and Game Mix sinks.
- Optional: setup the virtualAudio script to be run at login.  Otherwise, you will need to repeat the above step every time you restart your pc.

### Usage
- Set your applications to use Game Mix or Chat Mix sinks.
- Keep your system volume control on the Nova 7 sink to control master volume.
- The chat mix dial on your headset will now adjust the volume of your Game/Chat sinks.  The service polls the headset every 1 second and if there is a change in the mix level value, it will adjust the volume in the sinks.  