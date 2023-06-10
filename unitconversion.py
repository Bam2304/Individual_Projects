import tkinter as tk

# creating gui
root = tk.Tk()
root.geometry("700x700")
root.title("Unit Conversion")
root.configure(background="sky blue")
masterLabel = tk.Label(root, text="Welcome to Unit Converter!", width=20, height=2, bg="orange2")
masterLabel.place(x=250, y=5)

messageBoard = tk.Label(root, text="Thanks for Using!", width=40, height=5, bg="orange2")
messageBoard.place(x=175, y=600)


def toInches():  # covert cm to in
    try:
        before = float(height_input.get())
    except ValueError:
        messageBoard.config(text="That's an invalid input!")
    else:
        after = round(before/2.54, 2)
        messageBoard.config(text="Thanks for Using!")
        height_output.config(text=str(after))


def toCentimeters():  # convert in to cm
    try:
        before = float(height_input2.get())
    except ValueError:
        messageBoard.config(text="That's an invalid input!")
    else:
        after = round(before*2.54, 2)
        messageBoard.config(text="Thanks for Using!")
        height_output2.config(text=str(after))


def toPounds():  # convert kg to pounds
    try:
        before = float(height_input3.get())
    except ValueError:
        messageBoard.config(text="That's an invalid input!")
    else:
        after = round(before*2.205, 2)
        messageBoard.config(text="Thanks for Using!")
        height_output3.config(text=str(after))


def toKg():  # convert pounds to kg
    try:
        before = float(height_input4.get())
    except ValueError:
        messageBoard.config(text="That's an invalid input!")
    else:
        after = round(before/2.205, 2)
        messageBoard.config(text="Thanks for Using!")
        height_output4.config(text=str(after))


# Creating GUI

# Centimeters to Inches labels
height_input = tk.Entry(root)
height_input.place(x=150, y=50)

height_label = tk.Label(root, text="Centimeters", width=10, height=1, bg="yellow")
height_label.place(x=30, y=50)

height_outputL = tk.Label(root, text="Inches", width=10, height=1, bg="yellow")
height_outputL.place(x=360, y=50)

height_output = tk.Label(root, width=10, height=1, bg="white")
height_output.place(x=480, y=50)

convert = tk.Button(root, text="Convert", width=6, height=2, command=toInches)
convert.place(x=300, y=100)

# Inches to Centimeters labels
height_input2 = tk.Entry(root)
height_input2.place(x=150, y=200)

height_label2 = tk.Label(root, text="Inches", width=10, height=1, bg="yellow")
height_label2.place(x=30, y=200)

height_outputL2 = tk.Label(root, text="Centimeters", width=10, height=1, bg="yellow")
height_outputL2.place(x=360, y=200)

height_output2 = tk.Label(root, width=10, height=1, bg="white")
height_output2.place(x=480, y=200)

convert2 = tk.Button(root, text="Convert", width=6, height=2, command=toCentimeters)
convert2.place(x=300, y=250)


# Kilograms to pounds
height_input3 = tk.Entry(root)
height_input3.place(x=150, y=350)

height_label3 = tk.Label(root, text="Kilograms", width=10, height=1, bg="yellow")
height_label3.place(x=30, y=350)

height_outputL3 = tk.Label(root, text="Pounds", width=10, height=1, bg="yellow")
height_outputL3.place(x=360, y=350)

height_output3 = tk.Label(root, width=10, height=1, bg="white")
height_output3.place(x=480, y=350)

convert3 = tk.Button(root, text="Convert", width=6, height=2, command=toPounds)
convert3.place(x=300, y=400)


# Pounds to Kg
height_input4 = tk.Entry(root)
height_input4.place(x=150, y=500)

height_label4 = tk.Label(root, text="Pounds", width=10, height=1, bg="yellow")
height_label4.place(x=30, y=500)

height_outputL4 = tk.Label(root, text="Kilograms", width=10, height=1, bg="yellow")
height_outputL4.place(x=360, y=500)

height_output4 = tk.Label(root, width=10, height=1, bg="white")
height_output4.place(x=480, y=500)

convert4 = tk.Button(root, text="Convert", width=6, height=2, command=toKg)
convert4.place(x=300, y=550)


root.mainloop()