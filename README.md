# Arduino Dino Runner Game 🦕

A recreation of the classic Chrome Dino game running on Arduino Nano with a 16x2 I2C LCD display. Jump over cacti and see how long you can survive!

![Arduino Dino Game](https://img.shields.io/badge/Arduino-Nano-blue) ![License](https://img.shields.io/badge/License-MIT-green) ![Status](https://img.shields.io/badge/Status-Working-brightgreen)

## 🎮 Features

- **Classic Dino Runner Gameplay**: Jump over obstacles to survive
- **Progressive Difficulty**: Game speed increases as your score grows
- **Custom LCD Characters**: Pixel-perfect dino and cactus sprites
- **Sound Effects**: Buzzer plays game over sound
- **Score Tracking**: See how many obstacles you've cleared
- **Simple Controls**: One button to jump

## 🛠 Hardware Requirements

| Component | Quantity | Notes |
|-----------|----------|-------|
| Arduino Nano | 1 | Any Arduino board will work |
| 16x2 I2C LCD | 1 | Common HD44780 with I2C backpack |
| Push Button | 1 | Momentary switch |
| Buzzer | 1 | Active or passive buzzer |
| Jumper Wires | Several | For connections |
| Breadboard | 1 | Optional, for prototyping |

## 🔌 Wiring Diagram

```
Arduino Nano    →    Component
─────────────────────────────────
A4 (SDA)       →    LCD SDA
A5 (SCL)       →    LCD SCL
5V             →    LCD VCC
GND            →    LCD GND

D2             →    Button (one leg)
GND            →    Button (other leg)

D6             →    Buzzer (+)
GND            →    Buzzer (-)
```

## 📚 Required Libraries

Install these libraries through the Arduino IDE Library Manager:

- **LiquidCrystal_I2C** by Frank de Brabander
- **Wire** (included with Arduino IDE)

## 🚀 Installation

1. **Clone the repository:**
   ```bash
   git clone https://github.com/yourusername/arduino-dino-game.git
   cd arduino-dino-game
   ```

2. **Open in Arduino IDE:**
   - Open `dino_game.ino` in Arduino IDE

3. **Install libraries:**
   - Go to Tools → Manage Libraries
   - Search for "LiquidCrystal_I2C" and install

4. **Upload to Arduino:**
   - Connect your Arduino Nano
   - Select the correct board and port
   - Click Upload

## 🎯 How to Play

1. **Start**: Press the button to begin the game
2. **Jump**: Press the button to make the dino jump over cacti
3. **Survive**: Avoid hitting obstacles to increase your score
4. **Speed Up**: Game gets faster every 3 points
5. **Game Over**: Hit an obstacle and restart by pressing the button

## ⚙️ Configuration

### I2C LCD Address
If your LCD doesn't display anything, try changing the I2C address:
```cpp
LiquidCrystal_I2C lcd(0x3F, 16, 2);  // Try 0x3F instead of 0x27
```

### Game Speed
Adjust the starting speed and difficulty progression:
```cpp
int gameSpeed = 500;      // Starting speed (higher = slower)
gameSpeed -= 20;          // Speed increase per level
```

### Jump Duration
Modify how long the dino stays in the air:
```cpp
const int JUMP_DURATION = 3;  // Increase for longer jumps
```

## 🐛 Troubleshooting

**LCD shows nothing:**
- Check I2C address (try 0x27 or 0x3F)
- Verify wiring connections
- Check if LCD backlight is on

**Button doesn't work:**
- Ensure button is wired between D2 and GND
- Check if internal pullup is enabled (it is by default)
- Try a different button

**No sound:**
- Verify buzzer polarity
- Check if buzzer is active or passive type
- Test buzzer connection

**Game runs too fast/slow:**
- Adjust `gameSpeed` variable
- Modify speed increase rate

## 🎨 Customization Ideas

- **Add more obstacle types**: Create different cactus sprites
- **Power-ups**: Add special items that give temporary abilities
- **Day/night cycle**: Change display contrast based on score
- **High score saving**: Use EEPROM to save best scores
- **Two-player mode**: Add a second button and dino

## 📸 Demo

[Add your demo video or GIF here]

## 🤝 Contributing

Contributions are welcome! Here's how you can help:

1. Fork the repository
2. Create a feature branch (`git checkout -b feature/amazing-feature`)
3. Commit your changes (`git commit -m 'Add amazing feature'`)
4. Push to the branch (`git push origin feature/amazing-feature`)
5. Open a Pull Request

## 📄 License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.

## 🙏 Acknowledgments

- Inspired by Google Chrome's offline dinosaur game
- Thanks to the Arduino community for libraries and support
- Special thanks to [contributors](CONTRIBUTORS.md)

## 📞 Contact

- **GitHub**: [@Makuochukwu225](https://github.com/Makuochukwu225)
- **YouTube**: [Jaxlabs](https://www.youtube.com/@JaxLabs308)
- **Email**: officialrrye5@gmail.com

---

⭐ **Star this repo if you found it helpful!** ⭐
