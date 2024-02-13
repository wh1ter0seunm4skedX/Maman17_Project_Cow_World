# WanderField: The 3D Meadow

WanderField: The 3D Meadow is an interactive 3D application developed with OpenGL that simulates a serene meadow environment. Players control a detailed cow character, exploring a vast world filled with trees, animals, and various objects, some exhibiting reflective properties due to their metallic textures. This project aims to deliver an immersive experience through realistic models, environmental lighting, and user interaction.

## Features

- **Detailed 3D Cow Model:** Crafted with care, the cow model features a head, body, tail, legs, ears, nose, and eyes, assembled from spheres and ovals for a lifelike appearance.
- **Dynamic Environment:** Explore a large, open meadow populated with at least three additional objects, including trees and a metallic object, under the soft glow of ambient lighting.
- **Interactive Controls:** Direct the cow's movement, including its head, tail, and legs, through intuitive user inputs.
- **Customizable Lighting:** Adjust ambient light settings and manipulate a point light source's intensity, position, and direction for dynamic visual effects.
- **Texture Mapping:** Enhances the realism of the environment and the cow model with detailed textures.
- **Camera Controls:** Navigate the viewpoint with controls for position and orientation, including a first-person perspective through the cow's eyes.

## Getting Started

### Prerequisites

Ensure you have the following installed:
- OpenGL
- A compatible C++ compiler
- Any necessary libraries specific to your development environment

### Installation

1. Clone the repository:
   ```
   git clone https://github.com/wh1ter0seunm4skedX/WanderField-The-3D-Meadow.git
   ```
2. Navigate to the project directory:
   ```
   cd src
   ```
3. Compile the project (example using g++):
   ```
   g++ -o WanderField-The-3D-Meadow main.cpp -lGL -lGLU -lglut
   ```
4. Run the application:
   ```
   ./WanderField-The-3D-Meadow
   ```

## Usage

- **General Controls:** Navigate the in-game menu for options like adjusting ambient light or accessing help for controls.
- **Movement:** Use keyboard and mouse inputs to control the cow's movement, including walking, head tilting, and tail wagging.
- **Camera Views:** Switch between various camera angles, including a first-person view from the cow's perspective.

For detailed controls, refer to the in-game help menu.

## Contributing

Contributions are welcome! If you have ideas for new features, improvements, or bug fixes, please follow these steps:

1. Fork the repository.
2. Create your feature branch (`git checkout -b feature/AmazingFeature`).
3. Commit your changes (`git commit -m 'Add some AmazingFeature'`).
4. Push to the branch (`git push origin feature/AmazingFeature`).
5. Open a pull request.

## License

Distributed under the MIT License. See `LICENSE` for more information.

## Acknowledgments

- Special thanks to everyone who contributed to the development and testing of this project.
- Inspired by the beauty of natural landscapes and the complexity of 3D modeling.
