# GROUP-8-LABORATORY-4

Laboratory Assignment 4: Analog-to-Digital Conversion (ADC)

Learning Objectives:
Understand the concept of Analog-to-Digital Conversion.
Configure an STM32 ADC peripheral and its channels.
Read analog voltage values using the ADC.
Convert raw ADC readings into meaningful units (e.g., voltage, percentage).
Learn about different ADC conversion modes (single conversion, continuous, scan).


Prerequisites:
Completion of Lab 3.

A potentiometer or a simple analog sensor (like a photoresistor or thermistor with necessary resistors) connected to an ADC-capable pin on your board.

Assignment Description:

Create a new project or continue from a previous lab.

Configure an ADC peripheral (e.g., ADC1) and one of its channels connected to your analog input (potentiometer or sensor). Configure the ADC resolution (e.g., 12-bit). Reference the tutorials on DeepBlueEmbedded covering ADC.

In your main loop, trigger a single ADC conversion using HAL_ADC_Start() and HAL_ADC_PollForConversion(). Read the converted value using HAL_ADC_GetValue().

Convert the raw digital ADC value (0 to 2^N-1) into a voltage value (0 to Vref, usually 3.3V) or a scaled percentage (0-100%).

Send the converted value periodically (e.g., every 200ms) via UART to the terminal using the techniques from Lab 3.

Advanced: Configure the ADC for continuous conversion or scan mode to read multiple channels automatically. Explore using DMA for continuous, low-CPU-overhead data transfer from the ADC to memory.

Deliverables:

Your complete STM32CubeIDE project folder.

A short video demonstration showing the terminal output displaying the analog reading (voltage or percentage) as you adjust the potentiometer or change the sensor input.

A brief report explaining your ADC configuration and the conversion calculation from raw value to voltage/percentage. If attempting DMA, explain that configuration.
Optional Extensions: Interface with a second analog sensor. Implement a simple moving average filter on the ADC readings. Use an ADC reading to control a parameter in another lab (e.g., PWM duty cycle or LED blink rate).
