# E-Baja-Controller
This project is the VCU for Electric All Terrain Vehicle Electric designed for participating in E-Baja. The powertrain and control statergy was designed according to E-Baja Guidelines.

### Guidelines For Control Statergy
  - Brake Light should glow as the brake pedel is pressed. Brake Light should not glow when brake pedel is depressed.
  - Reverse Light & Reverse Alarm should operate when vehicle is in reverse mode.
  - Vehicle HV system should be disconnected when kill switch is engaged.
  - The HV system should only connect when
    1. Vehicle should be in Neutral Mode.
    2. Accelerator Pedel should be dispressed.
    3. Brake Pedel should be pressed.
    4. These condition when full filled and then only using some switch vehicle should connect HV and start.
  - When HV is connected then Tractive System Active Light (TSAL) should blink at 2-5Hz until the HV is connected.
  - Ready To Drive Sound (RTDS) should sound for 3-5sec whenever the vehicle HV is connected.

### Components Used
  - Arduino UNO
  - 4-Channel Relay Module
  - Pressure Switch
  - Pressure Pin Switch
  - 2 Way Switch
  - Key Switch
  - LED Light Amber Color (According to TSAL Guidelines)
  - LED Reverse Light (According to Reverse Light Guidelines)
  - LED Brake Light (According to Brake Light Guidelines)
  - Buzzer (According to RTDS & Reverse Alarm Guidelines)
  - Contacter (According to AIR Guidelines)
  - 12V Lithium/Lead Acid Battery
  - Fuse 10A Automotive

### Creator
  - Alakshendra Singh - Former Vice Captain of Team Aveon Racing
  - Team Aveon Racing
  - Suavy Technologies - Technology Partner & Sponser for Team Aveon Racing
  - Birla Institute of Technology Mesra - Host College & Sponser of Team Aveon Racing
