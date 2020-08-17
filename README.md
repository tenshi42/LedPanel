# Led Panel

This project is a DIY modular Led  display panel.

<img src="https://drive.google.com/uc?export=view&id=1UnPm1QKkGF1uB3NWWZct8VQoxh-T0akj"  width="400">
<img src="https://drive.google.com/uc?export=view&id=1UR8-hqlbHrao7ooin5BcgDJj3_vgskam-T0akj"  width="400">

Each block is made of 6 column and 7 row of red leds. 
Leds are controlled 2 collumns at a time (14 leds). 

The reason for this is that in the initial design, i wanted to control the whole panel with only 1 Arduino Nano, which one have only 12 Digital pins and 8 Analogic that can also be used as Digital ones. But as a block need 14 pins for the to control a 2 collumn set and 3 other pins to select the column set, a single Arduino Nano can only control 2 block.

# First version
The first working version used 1 Arduino Nano to control the columns electrical supply and 1 Raspberry PI 2 to control the individual leds of a column.
As a Raspberry PI is much powerful than an Arduino Nano, it was better for the leds control. The Arduino was now only used to switch the columns power state, one after the other, in order and in loop.
The Arduino was power by USB, connected to the Raspberry PI.
An additional wire was used between the Arduino and the Raspberry to force the synchronization of the 2 devices.
With this version, the panel was able to have up to 6 blocks but only 4 were mades as it take at least 4 hours to make a block.
<img src="https://drive.google.com/uc?export=view&id=1V-hEK3XBeY7f6BWFu626sgiSU2cghhXj"  width="400">
<img src="https://drive.google.com/uc?export=view&id=1Vi3ADw90A8voVcZ_Hnqlt7qwa2Lr3HtD"  width="400">

# Second version
The second version was made right after i receive my new Arduino Mega, which have 54 Digital pins and 16 Analogic pins.
As it had enough pins to handle itself the whole panel of 4 blocks, which means 28 pins, I move all the wire to the Arduino Mega Sensor Shield v2.0.
Now that there is only 1 device to control the panel, there in no more syncronisation problems and the panel can be driven by serial or any other comunication moudule as the Arduino Mega had 28 digital pins left !

<img src="https://drive.google.com/uc?export=view&id=1UV1w-VNGknujMfFwQaMb4J9AQgGO6ySy"  width="400">
<iframe src="https://drive.google.com/file/d/1UEGm_TBCiwB-6LCpGbMTuL6lmLDx_gqd/preview" width="640" height="480"></iframe>
[![Alternate Text]({image-url})]({https://drive.google.com/file/d/1UEGm_TBCiwB-6LCpGbMTuL6lmLDx_gqd/preview} "Link Title")