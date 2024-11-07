from PIL import Image
import os

# Load GIF
gif_path = 'anime.gif'
img = Image.open(gif_path)
frames = []
frame_count = img.n_frames

# Process each frame
for frame in range(frame_count):
    img.seek(frame)
    frame_rgb = img.convert("RGB").resize((70, 70))
    frame_data = []

    # Convert each pixel to RGB565 and store in frame_data
    for y in range(70):
        for x in range(70):
            r, g, b = frame_rgb.getpixel((x, y))
            rgb565 = ((r & 0xF8) << 8) | ((g & 0xFC) << 3) | (b >> 3)

            frame_data.append(rgb565)

    frames.append(frame_data)

with open("image_frames.h", "w") as f:
    f.write("#ifndef IMAGE_FRAMES_H\n#define IMAGE_FRAMES_H\n\n")
    for idx, frame in enumerate(frames):
        f.write(f"const uint16_t frame_{idx}[] = {{\n    ")
        f.write(", ".join(f"0x{pixel:04X}" for pixel in frame))
        f.write("\n};\n\n")
    f.write("#define FRAME_COUNT " + str(frame_count) + "\n")
    f.write("#endif\n")
