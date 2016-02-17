import xlrd
#----------------------------------------------------------------------
# This script used to fetch Xl sheet cells data fetching. 

def open_file(path):
    """
    Open and read an Excel file
    """
    workbook = xlrd.open_workbook(path)
    # get the worksheet
    sheet = workbook.sheet_by_name("facilitydata")
    #print sheet.nrows
    #print sheet.ncols
    n=0
    i=1
    for n in range(0,sheet.nrows):
        #print"main loop"
        #print n
        for i in range(1):
            #print"Inner loop"
            #print i
            LID=sheet.cell_value(n,1)+" "
            buildinName=sheet.cell_value(n,3)+" "
            floor=sheet.cell_value(n,4)+" "
            roomname=sheet.cell_value(n,5)+" "
            faciliTytype=sheet.cell_value(n,7)+" "
            print LID
            print buildinName
            print floor
            print faciliTytype
            print roomname
            filedata = None
            with open('facility.txt', 'r') as file :
                filedata = file.read()
            # Replace the target string
            filedata = filedata.replace('LOID', LID)
            filedata = filedata.replace('BUILDINGNAME', buildinName)
            filedata = filedata.replace('FLOOR', floor)
            filedata = filedata.replace('FACNAME', roomname)
            filedata = filedata.replace('FACILITYUSAGE', faciliTytype)
            # Write the file out again
            filename="facility"+ LID
            #print filename
            with open(filename+'.txt', 'w') as file:
                file.write(filedata)
            
                
        print "\n"

    

           
     
#----------------------------------------------------------------------
if __name__ == "__main__":
    path = "facilitydata.xlsx"
    open_file(path)
