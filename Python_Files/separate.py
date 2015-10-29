# Ptyhon program to organize files of a directory 
import os
import sys
import shutil

# This function organizes contents of sourcePath into multiple
# directories using the file types provided in extensionToDir
def OrganizeDirectory(sourcePath, extensionToDir):
    if not os.path.exists(sourcePath):
        print ("The source folder '" + sourcePath +
              "' does not exist!!\n")
    else:
        for file in os.listdir(sourcePath):
            file = os.path.join(sourcePath, file)

            # Ignore if its a directory
            if os.path.isdir(file):
                continue

            filename, fileExtension = os.path.splitext(file)
            fileExtension = fileExtension[1:]

            # If the file extension is present in the mapping
            if fileExtension in extensionToDir:

                # Store the corresponding directory name
                destinationName = extensionToDir[fileExtension]
                destinationPath = os.path.join(sourcePath, destinationName)

                # If the directory does not exist
                if not os.path.exists(destinationPath):
                    print ("Creating new directory for `" + fileExtension +
                          "` files, named - `" + destinationName + "'!!")

                    # Create a new directory
                    os.makedirs(destinationPath)

                # Move the file
                shutil.move(file, destinationPath)
            
                 

def main():

    if len(sys.argv) != 2:
        print "Usage: <program> <source path directory>"
        return

    sourcePath = sys.argv[1]

    extensionToDir = {}
    extensionToDir["mp3"] = "Songs"
    extensionToDir["jpg"] = "Images"
    extensionToDir["c"] = "C_Files"
    extensionToDir["cpp"] = "C++_Files"
    extensionToDir["py"] = "Python_Files"
    extensionToDir["jar"] = "JAR_Files"
    extensionToDir["png"] = "PNG_Files"
    extensionToDir["txt"] = "TEXT_Files"
    extensionToDir["ppt"] = "PPT_Files"
    extensionToDir["zip"] = "ZIP_Files"
    extensionToDir["apk"] = "Android_Files"
    extensionToDir["pdf"] = "PDF_Files"
    extensionToDir["deb"] = "DEBIAN_Files"
    print("")
    OrganizeDirectory(sourcePath, extensionToDir)

if __name__ == "__main__":
    main()
