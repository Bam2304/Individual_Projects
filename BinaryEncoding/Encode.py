import xlrd3


def code(file: str):
    file_name = file
    text = ""
    # Open the workbook and define the worksheet
    wb = xlrd3.open_workbook('EncodingTable.xlsx')
    # If given an error trying to run this line try: pip install xlrd==1.2.0
    # Using short character sheet first
    sh = wb.sheet_by_name('Sheet1')
    Bin2Char = {}
    # Create dictionary out of short characters
    for i in range(2, 18):
        # print(sh.cell(i, 2).value, " : ", sh.cell(i, 1).value)
        Bin2Char[sh.cell(i, 2).value] = sh.cell(i, 1).value
    # Change to long character sheet
    sh = wb.sheet_by_name('Sheet2')
    # Create dictionary out of long characters
    for i in range(2, 66):
        # print(sh.cell(i, 2).value, " : ", sh.cell(i, 1).value)
        if sh.cell(i, 2).value == "\\n":
            Bin2Char["\n"] = sh.cell(i, 1).value
        elif sh.cell(i, 2).value == "<space>":
            Bin2Char[" "] = sh.cell(i, 1).value
        elif type(sh.cell(i, 2).value) is float:
            Bin2Char[str(int(sh.cell(i, 2).value))] = sh.cell(i, 1).value
        else:
            Bin2Char[sh.cell(i, 2).value] = sh.cell(i, 1).value

    # Read in the text file
    with open(file_name, "r") as f:
        text = f.read()

    binString = ""
    for char in text:
        binString += Bin2Char[char]

    with open("binOutput.txt", "w") as f:
        f.write(str(len(binString)) + "." + binString)


#code("test2.txt")



