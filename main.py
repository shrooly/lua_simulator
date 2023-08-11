import numpy as np
import subprocess
import tkinter as tk
from PIL import Image, ImageTk
import os
from tkinter import scrolledtext

# Define the canvas dimensions
CANVAS_WIDTH = 296
CANVAS_HEIGHT = 128

# Create an empty canvas data array
canvas_data = np.zeros(CANVAS_WIDTH * CANVAS_HEIGHT, dtype=np.uint8)

# Create a Tkinter window
window = tk.Tk()
window.title("Canvas Visualization")

# Convert the canvas data to an image
canvas = canvas_data.reshape((CANVAS_HEIGHT, CANVAS_WIDTH))
image = Image.fromarray(canvas, 'L')
image = image.resize((CANVAS_WIDTH * 3, CANVAS_HEIGHT * 3), Image.NEAREST)  # Upscale the image for better visibility

# Convert the image to PhotoImage format (compatible with Tkinter)
photo_image = ImageTk.PhotoImage(image)

# Function to update the canvas with the input text
def update_canvas():
    text = text_widget.get("1.0", tk.END).strip()  # Get the text from the text widget
    # Call the C program with the input text as a command-line argument
    subprocess.run(["./build/lua_simulator", text], check=True)

    # After the subprocess is executed, update the canvas image by reading the file
    if os.path.exists("canvas_data.bin"):
        with open("canvas_data.bin", "rb") as file:
            canvas_data = file.read()
            canvas_array = np.frombuffer(canvas_data, dtype=np.uint8)
            canvas = canvas_array.reshape((CANVAS_HEIGHT, CANVAS_WIDTH))
            image = Image.fromarray(canvas, 'L')
            image = image.resize((CANVAS_WIDTH * 3, CANVAS_HEIGHT * 3), Image.NEAREST)
            photo_image.paste(image)
            canvas_label.config(image=photo_image)
    else:
        print("Binary does not exist!")

# Create a scrolled text widget for multiline input
text_widget = scrolledtext.ScrolledText(window, height=10, wrap=tk.WORD)
text_widget.pack(side=tk.LEFT, padx=10, pady=10)

# Create a button to trigger the canvas update
update_button = tk.Button(window, text="Update Canvas", command=update_canvas)
update_button.pack(side=tk.LEFT, padx=10, pady=5)

# Create a Tkinter label to display the image
canvas_label = tk.Label(window, image=photo_image)
canvas_label.pack(side=tk.LEFT, padx=10, pady=10)

# Start the Tkinter main loop
window.mainloop()
