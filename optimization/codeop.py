filepath = input("Enter path to input TAC file")
f = open(filepath, "r")


list_of_lines = f.readlines()
dictValues = dict()
constantFoldedList = []
print("Quadruple form after Constant Folding,constant propagation and copy propagation -")
print("-------------------------------------")
for i in list_of_lines:
    i = i.strip("\n")
    # if(i[0])
    # if(i[:5] == "print"):
    #     op = i[:5]
    #     arg1 = i[5:]
    op, arg1, arg2, res = i.split()
    if(op in ["+", "-", "*", "/", "<", ">", "<=", ">=", "==", "!="]):
        # constant folding
        if(arg1.isdigit() and arg2.isdigit()):
            result = eval(arg1+op+arg2)
            dictValues[res] = result
            print("=", result, "NULL", res)
            constantFoldedList.append(["=", result, "NULL", res])
        elif(arg1.isdigit()):
            # constant propagation
            if(arg2 in dictValues):
                if(dictValues[arg2].isdigit()):
                    result = eval(arg1+op+dictValues[arg2])
                    dictValues[res] = result
                    print("=", result, "NULL", res)
                    constantFoldedList.append(["=", result, "NULL", res])
                else:
                    arg2 = dictValues[arg2]
                    print(op, arg1, arg2, res)
                    constantFoldedList.append([op, arg1, arg2, res])
            else:
                print(op, arg1, arg2, res)
                constantFoldedList.append([op, arg1, arg2, res])
        elif(arg2.isdigit()):
            if(arg1 in dictValues):
                if(dictValues[arg1].isdigit()):
                    result = eval(dictValues[arg1]+op+arg2)
                    dictValues[res] = result
                    print("=", result, "NULL", res)
                    constantFoldedList.append(["=", result, "NULL", res])
                else:
                    arg1 = dictValues[arg1]
                    print(op, arg1, arg2, res)
                    constantFoldedList.append([op, arg1, arg2, res])
            else:
                print(op, arg1, arg2, res)
                constantFoldedList.append([op, arg1, arg2, res])
        else:
            flag1 = 0
            flag2 = 0
            arg1Res = arg1
            if(arg1 in dictValues):
                arg1Res = str(dictValues[arg1])
                flag1 = 1
            arg2Res = arg2
            if(arg2 in dictValues):
                arg2Res = str(dictValues[arg2])
                flag2 = 1
            if(flag1 == 1 and flag2 == 1):
                if(arg1Res.isdigit() & arg2Res.isdigit()):
                    result = eval(arg1Res+op+arg2Res)
                    dictValues[res] = result
                    print("=", result, "NULL", res)
                    constantFoldedList.append(["=", result, "NULL", res])
                else:
                    print(op, arg1Res, arg2Res, res)

            else:
                print(op, arg1Res, arg2Res, res)
                constantFoldedList.append([op, arg1Res, arg2Res, res])

    elif(op == "="):
        if(arg1.isdigit()):
            dictValues[res] = arg1
            print("=", arg1, "NULL", res)
            constantFoldedList.append(["=", arg1, "NULL", res])
        else:
            if(arg1 in dictValues):
                print("=", dictValues[arg1], "NULL", res)
                constantFoldedList.append(["=", dictValues[arg1], "NULL", res])
            else:
                dictValues[res] = arg1  # copy propagation
                print("=", arg1, "NULL", res)
                constantFoldedList.append(["=", arg1, "NULL", res])

    # elif(op in ["<",">","<=",">=","==","!="]):

    # if , goto s
    else:
        if(op == 'if'):
            if(arg1 in dictValues):
                arg1 = dictValues[arg1]

        print(op, arg1, arg2, res)
        constantFoldedList.append([op, arg1, arg2, res])
print(dictValues)
print(constantFoldedList)
print("\n")
print("Code after Constant Folding,constant propagation and copy propagation - ")
print("--------------------")
for i in constantFoldedList:
    if(i[0] == "="):
        print(i[3], i[0], i[1])
    elif(i[0] in ["+", "-", "*", "/", "==", "<=", "<", ">", ">="]):
        print(i[3], "=", i[1], i[0], i[2])
    elif(i[0] in ["if", "goto", "label", "not"]):
        if(i[0] == "if"):
            print(i[0], i[1], "goto", i[3])
        if(i[0] == "goto"):
            print(i[0], i[3])
        if(i[0] == "label"):
            print(i[3], ":")
        if(i[0] == "not"):
            print(i[3], "=", i[0], i[1])

print("\n")
print("After dead code elimination - ")
print("------------------------------")
for i in constantFoldedList:
    if(i[0] == "="):
        pass
    elif(i[0] in ["+", "-", "*", "/", "==", "<=", "<", ">", ">="]):
        print(i[3], "=", i[1], i[0], i[2])
    elif(i[0] in ["if", "goto", "label", "not"]):
        if(i[0] == "if"):
            if(i[1] == True):
                print("goto", i[3])
            elif(i[1] == False):
                pass
            else:
                print(i[0], i[1], "goto", i[3])
        if(i[0] == "goto"):
            print(i[0], i[3])
        if(i[0] == "label"):
            print(i[3], ":")
        if(i[0] == "not"):
            print(i[3], "=", i[0], i[1])
