#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define VOLUME_COMMAND_SIZE 38
#define SLEEP_PERIOD_SECONDS 1

int main( int argc, char *argv[] )
{
	FILE *fp;
	int flag = 0;
	int mixLevel = 0;
	int gameLevel = 100;
	int chatLevel = 100;
	int lastMixLevel = 0;
	char gameVolumeCommand[VOLUME_COMMAND_SIZE];
	char chatVolumeCommand[VOLUME_COMMAND_SIZE];

	while(1){
		//Open a process with headsetcontrol
		fp = popen("headsetcontrol -m -c", "r");
		if (fp == NULL) {
			printf("Failed to run command\n" );
			exit(EXIT_FAILURE);
		}

		//Read Result of command then close process
		fscanf(fp,"%d",&mixLevel);
		pclose(fp);

		//If no change in volume mix and not the first run cycle, sleep and then continue cycle
		if(lastMixLevel == mixLevel && flag){
			sleep(SLEEP_PERIOD_SECONDS);
			continue;
		}

		//Calculate Volume Mix
		if(mixLevel > 64){
			gameLevel = 200-(mixLevel*100/64);
			chatLevel = 100;
		}
		else if(mixLevel < 64){
			gameLevel = 100;
			chatLevel = (mixLevel*100/64);
		}
		else{
			gameLevel = 100;
			chatLevel = 100;
		}

		lastMixLevel = mixLevel;

		//Create Set Volume Commands
		snprintf(gameVolumeCommand, VOLUME_COMMAND_SIZE, "pactl -- set-sink-volume GameMix %d%%", gameLevel);
		snprintf(chatVolumeCommand, VOLUME_COMMAND_SIZE, "pactl -- set-sink-volume ChatMix %d%%", chatLevel);

		//Run volume commands
		// system(gameVolumeCommand);
		// system(chatVolumeCommand);
		fp = popen(gameVolumeCommand, "r");
		if (fp == NULL) {
			printf("Failed to run Game Volume command\n" );
			exit(EXIT_FAILURE);
		}
		pclose(fp);
		// system(chatVolumeCommand);
		fp = popen(chatVolumeCommand, "r");
		if (fp == NULL) {
			printf("Failed to run Chat Volume command\n" );
			exit(EXIT_FAILURE);
		}
		pclose(fp);

		//DEBUGGING - Log levels to stdin
		//printf("Mix Level: %d\n", mixLevel);
		//printf("Game Volume: %d%%\n", gameLevel);
		//printf("Chat Volume: %d%%\n", chatLevel);

		//Sleep to free up cpu processing
		sleep(SLEEP_PERIOD_SECONDS);

		//Set flag to indicate the loop has run at least once
		flag = 1;
	}

	return EXIT_SUCCESS;
}
