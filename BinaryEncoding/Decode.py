import xlrd3


def decode(file="binOutput.txt"):  # defaults to binOutput
    values = []
    # Open the workbook and define the worksheet
    wb = xlrd3.open_workbook('Team2Table.xlsx')
    # Using short character sheet first
    sh = wb.sheet_by_name('Sheet1')
    Bin2Char = {}
    # Create dictionary out of short binary
    for i in range(2, 18):
        # print(sh.cell(i, 1).value, " : ", sh.cell(i, 2).value)
        Bin2Char[sh.cell(i, 1).value] = sh.cell(i, 2).value
    # Change to long character sheet
    sh = wb.sheet_by_name('Sheet2')
    # Create dictionary out of long binary
    for i in range(2, 66):
        # print(sh.cell(i, 1).value, " : ", sh.cell(i, 2).value)
        Bin2Char[sh.cell(i, 1).value] = sh.cell(i, 2).value

    # Read in the binary file

    with open(file, "r") as f:
        text = f.read()
        actual = text.split(".")  # this is so that only the binary part is read, not the decimal

    # actual[1] contains only the string of binary numbers we want to read
    bin_string = actual[1]
    while bin_string:
        if bin_string[0] == "1":  # if the first number is 1(long character), slice the first 7 numbers into sub
            sub = bin_string[:7]
            values.append(sub)  # put sub into the values list
            bin_string = bin_string.removeprefix(sub)  # remove sub from the string of binary numbers
        elif bin_string[0] == "0":  # first number 0 (short character), slice first 5 numbers and put into sub
            sub = bin_string[:5]
            values.append(sub)
            bin_string = bin_string.removeprefix(sub)

    original_text = ""
    for item in values:  # converting some characters to their python equivalents
        if Bin2Char[item] == "\\n":
            Bin2Char[item] = "\n"
        elif Bin2Char[item] == "<space>":
            Bin2Char[item] = " "
        elif type(Bin2Char[item]) is float:
            Bin2Char[item] = str(int(Bin2Char[item]))
        original_text = original_text + Bin2Char[item]  # assembling the original text back to letters

    # write the original text to TextOutput.txt
    with open("TextOutput.txt", "w") as f:
        f.write(original_text)


# run function with desired input
decode()

