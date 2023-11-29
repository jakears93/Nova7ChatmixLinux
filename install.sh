#!/bin/bash

if ! which headsetcontrol > /dev/null 2>&1; then
	echo "Headset control must be installed."
	exit 1
fi

#Determine version to use
virtualAudioExe=""
if which pulseaudio > /dev/null 2>&1; then
	echo "Installing PulseAudio Version"
	virtualAudioExe="virtualAudioPulse"
elif which pipewire > /dev/null 2>&1; then
	echo "Installing Pipewire version"
	virtualAudioExe="virtualAudioPipewire"
else
	echo "System must have Pipewire or PulseAudio installed"
	exit 1
fi

#Build binary
make

#Create service and register
sudo cp nova-mixer.service /usr/lib/systemd/user/nova-mixer.service
systemctl --user enable nova-mixer
systemctl --user start nova-mixer

#Copy binary to bin and clean up
sudo cp nova7Mixer /usr/local/bin/nova7Mixer
sudo cp ${virtualAudioExe} /usr/local/bin/virtualAudio
make clean
