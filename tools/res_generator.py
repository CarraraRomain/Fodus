import json


matrix3x3 = [["" for y in range(3)] for x in range(3)]
matrix2x2 = [["" for y in range(2)] for x in range(2)]
matrix3x2 = [["" for y in range(2)] for x in range(3)]
matrix2x3 = [["" for y in range(3)] for x in range(2)]
matrix1x3 = [["" for y in range(3)] for x in range(1)]
matrix1x2 = [["" for y in range(2)] for x in range(1)]
matrix1x1 = [["" for y in range(1)] for x in range(1)]

# Matrix of prefixes
# matrixXxY
#         X  Y
matrix3x3[0][0] = "TOP_LEFT"
matrix3x3[1][0] = "TOP_MID"
matrix3x3[2][0] = "TOP_RIGHT"
matrix3x3[0][1] = "MID_LEFT"
matrix3x3[1][1] = "MID_MID"
matrix3x3[2][1] = "MID_RIGHT"
matrix3x3[0][2] = "BOT_LEFT"
matrix3x3[1][2] = "BOT_MID"
matrix3x3[2][2] = "BOT_RIGHT"

matrix2x2[0][0] = "TOP_LEFT"
matrix2x2[1][0] = "TOP_RIGHT"
matrix2x2[0][1] = "BOT_LEFT"
matrix2x2[1][1] = "BOT_RIGHT"

matrix3x2[0][0] = "TOP_LEFT"
matrix3x2[1][0] = "TOP_MID"
matrix3x2[2][0] = "TOP_RIGHT"
matrix3x2[0][1] = "BOT_LEFT"
matrix3x2[1][1] = "BOT_MID"
matrix3x2[2][1] = "BOT_RIGHT"

matrix2x3[0][0] = "TOP_LEFT"
matrix2x3[1][0] = "TOP_RIGHT"
matrix2x3[0][1] = "MID_LEFT"
matrix2x3[1][1] = "MID_RIGHT"
matrix2x3[0][2] = "BOT_LEFT"
matrix2x3[1][2] = "BOT_RIGHT"
#         X  Y
matrix1x3[0][0] = "TOP"
matrix1x3[0][1] = "MID"
matrix1x3[0][2] = "BOT"

matrix1x2[0][0] = "TOP"
matrix1x2[0][1] = "BOT"

matrix1x1[0][0] = "ALONE"


def initialize_file():

    print("Init File struct...")
    return {"header": {"name": "Default Tileset", "version": "0.2"}, "tiles": {}}


def create_res():
    name = input("New res name: ")
    suffix = input("suffix: ")
    X = int(input("X size: "))
    Y = int(input("Y size: "))
    Xori = int(input("X origin: "))
    Yori = int(input("Y origin: "))
    result = {}
    prefix = ""
    for i in range(X):
        for j in range(Y):
            if X == 3 and Y == 3:
                prefix = matrix3x3[i][j]
            if X == 3 and Y == 2:
                prefix = matrix3x2[i][j]
            if X == 2 and Y == 3:
                prefix = matrix2x3[i][j]
            if X == 1 and Y == 3:
                prefix = matrix1x3[i][j]
            if X == 1 and Y == 2:
                prefix = matrix1x2[i][j]
            if X == 2 and Y == 2:
                prefix = matrix2x2[i][j]
            full_name = name+"_"+prefix
            full_name = full_name + "_" + suffix if (suffix != "") else full_name
            result.update({full_name: {"x": Xori+i, "y": Yori+j}})
    print("Generating " + name + "...")
    return result


print("*** Fodus JSON Res Generator ***")
print(" *-> X")
print(" | ")
print(" v ")
print(" Y ")
print("=========")
filename = input("Tile file name: ")
print("=========")
with open("tiles.json", "r+") as jsonfile:
    print("Open file " + filename + ".json")
    try:
        data = json.load(jsonfile)
    except ValueError:
        print("Empty file found")
        data = initialize_file()

    for key in data['tiles'].keys():
        print("Found : " + key)

    print("=========")
    rc = input("Create new res? (y/n) ")
    print("=========")
    while rc != "n":
        data['tiles'].update(create_res())
        print("=========")
        rc = input("Create new res? (y/n) ")

    if data:
        jsonfile.seek(0)
        jsonfile.truncate(0)
        json.dump(data, jsonfile, indent=2)
