# First, install the required dependencies
sudo apt-get update && sudo apt-get upgrade
sudo apt-get install gcc make xorg libxext-dev libbsd-dev

# Create a directory for MLX and clone the repository
mkdir mlx_linux
cd mlx_linux
git clone https://github.com/42Paris/minilibx-linux.git .
# or alternatively:
# wget https://github.com/42Paris/minilibx-linux/archive/refs/heads/master.zip
# unzip master.zip
# mv minilibx-linux-master/* .

# Compile MLX
make

# Copy the MLX files to the system folders
sudo cp mlx.h /usr/include
sudo cp libmlx.a /usr/lib
