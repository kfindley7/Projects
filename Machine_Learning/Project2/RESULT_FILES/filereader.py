import re
import csv

algs = ["RHC", "GA", "SA", "MIMIC"]
testTypes = ["FourPeaksTest", "MaxKColorTest", "TravelingSalesmanTest"]

for alg in algs:
    for test in testTypes:
        filename = test + alg + ".txt"
        file = open(filename, "r")

        newFile = open(test + alg + "Results.csv", "w")
        writer = csv.writer(newFile)
        formattedFile = []

        lines = file.readlines()
        for line in lines[2:]:
            numbers = re.findall("((?:1*\.*0*E*)\d+\.*\d*)", line)
            if (numbers != []):
                formattedFile.append(numbers)
        lineNum = 0
        count = 1
        superFormattedFile = []
        while (lineNum + count) < len(formattedFile):
            line = formattedFile[lineNum]
            newLine = line + formattedFile[lineNum + count] + formattedFile[lineNum + count + 1]
            superFormattedFile.append(newLine)
            lineNum += 3

        infoDict = {}
        for line in superFormattedFile:
            index = 0
            for num in line[0:-2]:
                if alg == "RHC":
                    key = "Iterations " + num
                    if index == 0:
                        if key not in infoDict.keys():
                            infoDict[key] = [1, float(line[-2])]
                        else:
                            infoDict[key][1] += float(line[-2])
                            infoDict[key][0] += 1
                elif alg == "GA":
                    if index == 0:
                        key = "Iterations " + num
                        if key not in infoDict.keys():
                            infoDict[key] = [1, float(line[-2])]
                        else:
                            infoDict[key][1] += float(line[-2])
                            infoDict[key][0] += 1
                    elif index == 1:
                        key = "Population Size " + num
                        if key not in infoDict.keys():
                            infoDict[key] = [1, float(line[-2])]
                        else:
                            infoDict[key][1] += float(line[-2])
                            infoDict[key][0] += 1
                    elif index == 2:
                        key = "Matings " + num
                        if key not in infoDict.keys():
                            infoDict[key] = [1, float(line[-2])]
                        else:
                            infoDict[key][1] += float(line[-2])
                            infoDict[key][0] += 1
                    elif index == 3:
                        key = "Mutations " + num
                        if key not in infoDict.keys():
                            infoDict[key] = [1, float(line[-2])]
                        else:
                            infoDict[key][1] += float(line[-2])
                            infoDict[key][0] += 1
                elif alg == "SA":
                    if index == 0:
                        key = "Iterations " + num
                        if key not in infoDict.keys():
                            infoDict[key] = [1, float(line[-2])]
                        else:
                            infoDict[key][1] += float(line[-2])
                            infoDict[key][0] += 1
                    elif index == 1:
                        key = "Initial Temperature " + num
                        if key not in infoDict.keys():
                            infoDict[key] = [1, float(line[-2])]
                        else:
                            infoDict[key][1] += float(line[-2])
                            infoDict[key][0] += 1
                    elif index == 2:
                        key = "Cooling Exponent " + num
                        if key not in infoDict.keys():
                            infoDict[key] = [1, float(line[-2])]
                        else:
                            infoDict[key][1] += float(line[-2])
                            infoDict[key][0] += 1
                elif alg == "MIMIC":
                    if index == 0:
                        key = "Iterations " + num
                        if key not in infoDict.keys():
                            infoDict[key] = [1, float(line[-2])]
                        else:
                            infoDict[key][1] += float(line[-2])
                            infoDict[key][0] += 1
                    elif index == 1:
                        key = "Samples " + num
                        if key not in infoDict.keys():
                            infoDict[key] = [1, float(line[-2])]
                        else:
                            infoDict[key][1] += float(line[-2])
                            infoDict[key][0] += 1
                    elif index == 2:
                        key = "Samples to Keep " + num
                        if key not in infoDict.keys():
                            infoDict[key] = [1, float(line[-2])]
                        else:
                            infoDict[key][1] += float(line[-2])
                            infoDict[key][0] += 1
                index += 1
        keyList = list(infoDict.keys())
        keyList.sort(key=str.lower, reverse=True)
        for key in infoDict.keys():
            infoDict[key] = infoDict[key][1] / infoDict[key][0]
        writer.writerow(["Parameter", "Average Optimal Value"])
        for key in keyList:
            writer.writerow([key, infoDict[key]])

        writer.writerow([lines[0]])
        labels = ["Iterations"]
        if alg == "GA":
            labels += ["Population Size","Matings", "Mutations"]
        elif alg == "SA":
            labels += ["Initial Temperature", "Cooling Exponent"]
        elif alg == "MIMIC":
            labels += ["Samples", "Samples to Keep"]
        labels += ["Optimal Value", "Time"]
        writer.writerow(labels)
        for line in superFormattedFile:
            writer.writerow(line)
        file.close()
        newFile.close()
