HOW TO DEBUG AN ESP32-S3 USING PLATFORMIO

Using a dual environment that selects between DEBUG or RELEASE and which effectively stops in the setup() function when debugging

To select either the DEBUG or RELEASE environments click the env button in the status bar, then select one from the text box on the menu bar

Working Debug Procedure for ESP32-S3 setup()

 1: Start Debug (with or without uploading)
 2: Debug toolbar appears - Shows pause, reset and stop buttons
 3: Click Pause - Manually halt execution
 4: Stops in bootloader file - esp_pm_impl_waiti.dbgasm (line 3)
 5: Click Continue - Lets it run to your breakpoint
 6: Stops at while (stop_here) // Set a breakpoint at this line the spin loop in setup()
 7: Clicking continue (F5) at this point just cycles around and stops again at the stop_here breakpoint
 8: Change the value of a variable - Right-click stop_here in Local variables → Set Value → 0 → Enter
 9: Step through setup() - Use F10 (Step Over) to go line by line
10: Continue to loop() - At end of setup() at the last line of code, press F5 (Continue) to reach loop()

