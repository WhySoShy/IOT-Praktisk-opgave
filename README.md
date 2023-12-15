### Description
The program allows 2 Arduino boards to talk to each other through Serial `RX/TX`, to let each other know what `X/Y Position`, `X/Y Direction` and the index of our ball it should start in, when getting transfered from one 
screen to another.

#### *Disclaimer*
We are using an `Arduino Zero` for both boards, and the Setup has only been made for that board. </br >
other boards could work but have not been tested.

---

### Setup
You connect 2 Arduino boards together through a Serial connection. Your boards should Cross the `RX/TX`. </br >
<details>
<summary>Specific connections.</summary>
<u>Board 1's connection:</u>

`RX` -> `TX` </br >
`XT` -> `RX`

<u> Board 2's connection:</u>

`TX` -> `RX` </br >
`RX` -> `TX`

---
</details>

Connect 1 OLED Screen to each of your boards.

`SDA` -> `SDA` </br >
`SCL` -> `SCL` </br >
`VCC` -> `3.3V` </br >
`GND` </br >
Your 2 boards should have a common ground that you use. </br >
Upload the (program)[https://github.com/WhySoShy/IOT-Praktisk-opgave/tree/master/Ball_collision] and run it.

### Errors
#### None of the balls are showing?
Try resetting the board that has `atRight` to true. </br >
#### Why is my ball stuck?
Sometimes the balls can be stuck on the Y Axis, when it reaches absolute 0. We have tried to fix this issue, but it could still occur.

### Libraries
| Name | Version | Used for |
| ---- | ------- | -------- |
| [Adafruit SSD1306](https://github.com/adafruit/Adafruit_SSD1306) | `2.5.9`  | To control the SSD1306 OLED |
| [Adafruit GFX](https://github.com/adafruit/Adafruit-GFX-Library) | `1.11.9` | Used to draw on the OLED display. |
| Arduino | `BUILT IN` | Needed to access Arduino functions. |
| WIRE    | `BUILT IN` | Used to handle the OLED Display. |
| Stdlib  | `BUILT IN` | Used to generate a more random path for our ball.  |

### Configuration
| Type | Name       | Description |
| ---- | ---------- | ----------- |
| bool | AtRight    | Determines what side should be collideable and where the balls should start. |
| bool | isOnScreen | Determines if it should show the ball on the screen.                         |
| bool | debug      | Lets you see debug messages in the Serial Monitor.                           |
