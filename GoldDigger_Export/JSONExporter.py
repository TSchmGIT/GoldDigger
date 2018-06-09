sourceFile = "Resources/PropertyFuelTank.json"
templateFile = "Templates/PropertyTemplate.h"

with open(sourceFile) as f:
    import json
    jsonData = json.load(f)


with open(templateFile) as f:
    templateFileString = f.read()

# Collect basic template fields from json
propertyName = jsonData["name"]
attributeList = jsonData["attributes"]

# replace template fields
finalFileString = templateFileString.replace("{{PropertyName}}", propertyName)

# write attribute methods
methodBeginTag = "{{SingleAttributeMethodBegin}}"
methodEndTag = "{{SingleAttributeMethodEnd}}"

methodBeginIndex = templateFileString.index(methodBeginTag)
methodEndIndex =  templateFileString.index(methodEndTag)

attributeListStartIndex = methodBeginIndex + len(methodBeginTag) + 1
attributeListEndIndex = methodEndIndex - 1

singleAttributeTemplateString = templateFileString[attributeListStartIndex:attributeListEndIndex]

completeAttributeMethodString = ""
for attribute in attributeList:
    attributeType = attribute["type"]
    attributeName = attribute["name"]

    attributeMethodString = singleAttributeTemplateString
    attributeMethodString = attributeMethodString.replace("{{AttributeType}}", attributeType)
    attributeMethodString = attributeMethodString.replace("{{AttributeName}}", attributeName)
    completeAttributeMethodString += attributeMethodString + "\n"

replacedSubString = templateFileString[methodBeginIndex : methodEndIndex + len(methodEndTag)]
finalFileString = finalFileString.replace(replacedSubString, completeAttributeMethodString)

# write attribute list
attributeListBeginTag = "{{AttributeListBegin}}"
attributeListEndTag = "{{AttributeListEnd}}"

attributeListBeginIndex = templateFileString.index(attributeListBeginTag)
attributeListEndIndex =  templateFileString.index(attributeListEndTag)

attributeListStartIndex = attributeListBeginIndex + len(attributeListBeginTag) + 1
attributeListEndIndex = attributeListEndIndex - 1

singleAttributeTemplateString = templateFileString[attributeListStartIndex:attributeListEndIndex]

completeAttributeListString = ""
for attribute in attributeList:
    attributeType = attribute["type"]
    attributeName = attribute["name"]
    attributeDefaultValue = attribute["defaultValue"]

    attributeString = singleAttributeTemplateString
    attributeString = attributeString.replace("{{AttributeType}}", str(attributeType))
    attributeString = attributeString.replace("{{AttributeName}}", "m_" + str(attributeName))
    attributeString = attributeString.replace("{{AttributeDefaultValue}}", str(attributeDefaultValue))
    completeAttributeListString += attributeString + "\n"

replacedSubString = templateFileString[attributeListBeginIndex : attributeListEndIndex + len(attributeListEndTag)]
finalFileString = finalFileString.replace(replacedSubString, completeAttributeListString)


# write final data to file
targetFilename = propertyName + ".h"
with open(targetFilename, "w") as finalFile:
    finalFile.write(finalFileString)