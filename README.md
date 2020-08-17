# Led Panel

This project is a DIY modular Led  display panel.

Each block is made of 6 column and 7 row of red leds. 
Leds are controlled 2 collumns at a time (14 leds). 

The reason for this is that in the initial design, i wanted to control the whole panel with only 1 Arduino Nano, which one have only 12 Digital GPIO and 8 Analogic that can also be used as Digital ones. But as a block need 14 GPIO for the to control a 2 collumn set and 3 other GPIO to select the column set, a single Arduino Nano can only control 2 block.

The first working version used 1 Arduino Nano to control the columns electrical supply and 1 Raspberry PI 2 to control the individual leds of a column.
As a Raspberry PI is much powerful than an Arduino Nano, it was better for the leds control. The Arduino was now only used to switch the columns power state, one after the other, in order and in loop.
The Arduino was power by USB, connected to the Raspberry PI.
An additional wire was used between the Arduino and the Raspberry to force the synchronization of the 2 devices.
With this version, the panel was able to have up to 6 blocks but only 4 were mades as it take at least 4 hours to make a block.
![alt text](https://drive.google.com/uc?export=view&id=1V-hEK3XBeY7f6BWFu626sgiSU2cghhXj "Logo Title Text 1")
<img src="https://drive.google.com/uc?export=view&id=1V-hEK3XBeY7f6BWFu626sgiSU2cghhXj"  width="120" height="120">