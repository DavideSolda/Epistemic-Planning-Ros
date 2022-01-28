#!usr/bin/env python
import os

def writeColorCross(color, f):
    f.write("not_ok(T) :- time(T), not "+color+"CrossOk(T).")

    f.write(""+color+"CrossOk(T) :- holds(has_pos(back, "+color+") , T), holds(has_pos(up, white), T), holds(has_col(white, 1, white), T), holds(has_col("+color+", 5, "+color+") , T), time(T).\n")
    f.write(""+color+"CrossOk(T) :- holds(has_pos(right, "+color+") , T), holds(has_pos(up, white), T), holds(has_col(white, 3, white), T), holds(has_col("+color+", 7, "+color+") , T), time(T).\n")
    f.write(""+color+"CrossOk(T) :- holds(has_pos(fore, "+color+") , T), holds(has_pos(up, white), T), holds(has_col(white, 5, white), T), holds(has_col("+color+", 1, "+color+") , T), time(T).\n")
    f.write(""+color+"CrossOk(T) :- holds(has_pos(left, "+color+") , T), holds(has_pos(up, white), T), holds(has_col(white, 7, white), T), holds(has_col("+color+", 3, "+color+") , T), time(T).\n")


    f.write(""+color+"CrossOk(T) :- holds(has_pos(up, "+color+") , T), holds(has_pos(fore, white), T), holds(has_col(white, 1, white), T), holds(has_col("+color+", 5, "+color+") , T), time(T).\n")
    f.write(""+color+"CrossOk(T) :- holds(has_pos(right, "+color+") , T), holds(has_pos(fore, white), T), holds(has_col(white, 3, white), T), holds(has_col("+color+", 5, "+color+") , T), time(T).\n")
    f.write(""+color+"CrossOk(T) :- holds(has_pos(down, "+color+") , T), holds(has_pos(fore, white), T), holds(has_col(white, 7, white), T), holds(has_col("+color+", 5, "+color+") , T), time(T).\n")
    f.write(""+color+"CrossOk(T) :- holds(has_pos(left, "+color+") , T), holds(has_pos(fore, white), T), holds(has_col(white, 5, white), T), holds(has_col("+color+", 1, "+color+") , T), time(T).\n")

    f.write(""+color+"CrossOk(T) :- holds(has_pos(up, "+color+") , T), holds(has_pos(back, white), T), holds(has_col(white, 5, white), T), holds(has_col("+color+", 1, "+color+") , T), time(T).\n")
    f.write(""+color+"CrossOk(T) :- holds(has_pos(right, "+color+") , T), holds(has_pos(back, white), T), holds(has_col(white, 3, white), T), holds(has_col("+color+", 1, "+color+") , T), time(T).\n")
    f.write(""+color+"CrossOk(T) :- holds(has_pos(down, "+color+") , T), holds(has_pos(back, white), T), holds(has_col(white, 1, white), T), holds(has_col("+color+", 5, "+color+") , T), time(T).\n")
    f.write(""+color+"CrossOk(T) :- holds(has_pos(left, "+color+") , T), holds(has_pos(back, white), T), holds(has_col(white, 7, white), T), holds(has_col("+color+", 1, "+color+") , T), time(T).\n")

    f.write(""+color+"CrossOk(T) :- holds(has_pos(up, "+color+") , T), holds(has_pos(right, white), T), holds(has_col(white, 7, white), T), holds(has_col("+color+", 3, "+color+") , T), time(T).\n")
    f.write(""+color+"CrossOk(T) :- holds(has_pos(fore, "+color+") , T), holds(has_pos(right, white), T), holds(has_col(white, 5, white), T), holds(has_col("+color+", 3, "+color+") , T), time(T).\n")
    f.write(""+color+"CrossOk(T) :- holds(has_pos(down, "+color+") , T), holds(has_pos(right, white), T), holds(has_col(white, 3, white), T), holds(has_col("+color+", 3, "+color+") , T), time(T).\n")
    f.write(""+color+"CrossOk(T) :- holds(has_pos(back, "+color+") , T), holds(has_pos(right, white), T), holds(has_col(white, 1, white), T), holds(has_col("+color+", 3, "+color+") , T), time(T).\n")

    f.write(""+color+"CrossOk(T) :- holds(has_pos(up, "+color+") , T), holds(has_pos(left, white), T), holds(has_col(white, 3, white), T), holds(has_col("+color+", 7, "+color+") , T), time(T).\n")
    f.write(""+color+"CrossOk(T) :- holds(has_pos(fore, "+color+") , T), holds(has_pos(left, white), T), holds(has_col(white, 5, white), T), holds(has_col("+color+", 7, "+color+") , T), time(T).\n")
    f.write(""+color+"CrossOk(T) :- holds(has_pos(back, "+color+") , T), holds(has_pos(left, white), T), holds(has_col(white, 7, white), T), holds(has_col("+color+", 7, "+color+") , T), time(T).\n")
    f.write(""+color+"CrossOk(T) :- holds(has_pos(down, "+color+") , T), holds(has_pos(left, white), T), holds(has_col(white, 1, white), T), holds(has_col("+color+", 7, "+color+") , T), time(T).\n")

    f.write(""+color+"CrossOk(T) :- holds(has_pos(fore,  "+color+") , T),   holds(has_pos(down, white), T), holds(has_col(white, 1, white), T), holds(has_col("+color+", 5, "+color+") , T), time(T).\n")
    f.write(""+color+"CrossOk(T) :- holds(has_pos(right, "+color+") , T), holds(has_pos(down, white), T), holds(has_col(white, 3, white), T), holds(has_col("+color+", 3, "+color+") , T), time(T).\n")
    f.write(""+color+"CrossOk(T) :- holds(has_pos(back,  "+color+") , T), holds(has_pos(down, white), T), holds(has_col(white, 5, white), T), holds(has_col("+color+", 1, "+color+") , T), time(T).\n")
    f.write(""+color+"CrossOk(T) :- holds(has_pos(left,  "+color+") , T), holds(has_pos(down, white), T), holds(has_col(white, 7, white), T), holds(has_col("+color+", 7, "+color+") , T), time(T).\n")

def defineGoal(j):
    f=open("temp/addGoals4Rubik.lp", "w")
    if (j==0):
        writeColorCross("orange", f)
    if (j==1):
        writeColorCross("orange", f)
        writeColorCross("red", f)
    elif (j==2):
        writeColorCross("orange", f)
        writeColorCross("red", f)
        writeColorCross("green", f)
    elif (j==3):
        writeColorCross("orange", f)
        writeColorCross("red", f)
        writeColorCross("green", f)
        writeColorCross("blue", f)
    f.close()

class Action:
    action=""
    index=0
    def __init__(self, a, i):
        self.action=a
        self.index=i
    def __repr__(self):
        return self.action+"\t\t"+str(self.index)
    def __str__(self):
        return self.action+"\t\t"+str(self.index)

def checkUNSATISFIABLE():
    f=open("temp/res.txt", "r")
    restxt=f.readlines()
    print(restxt[0])
    print(restxt[-1])
    return "UNSATISFIABLE" in restxt[-7]

if __name__ == "__main__":
    os.system("python A/writeRulesInA.py")
    os.system("make")
    os.system("cp A/initially.A temp/initially.A")

    f=open("temp/res.txt", "w")
    f.close()
    actionsFile=open("output/actions.txt", "w")#clean that file
    actionsFile.close()
    for i in range(0,4):
        
        defineGoal(i)

        print("Iterazione numero "+str(i))

        os.system("cat A/Rotations.A temp/finally.A temp/initially.A > temp/istance.A")
        os.system("./TestGramm <temp/istance.A")
        
        f=open("temp/res.txt", "w")
        f.close()
        lengthPath=2

        restxt=[]
        while(lengthPath ==2 or checkUNSATISFIABLE() ):
            fileLength=open("temp/lengthPath.lp", "w")
            fileLength.write("#const l="+str(lengthPath)+".\n")
            fileLength.close()

            os.system("clingo --config=tweety -t 7 lp/add4Rubik.lp lp/clingoIstance.lp temp/addGoals4Rubik.lp temp/lengthPath.lp > temp/res.txt")

            lengthPath=1+lengthPath
            
        os.system("cp temp/res.txt output/risultato.txt")
        os.system("cat temp/res.txt | tail -8 | head -1 > temp/resTemp.txt; mv temp/resTemp.txt temp/res.txt")
        f=open("temp/res.txt")
        lines=f.readlines()
        splitedString = lines[0].split(" ")
        splitedString[-1]=splitedString[-1][:-1]
        f.close()
        f=open("temp/initially.A", "w")
        actionList=[]
        for el in splitedString:#holds(has_col(C,P,C1),l)
            if (el[0]=="h"):
                t=int(el[el.rfind(",")+1:-1])
                #print(t)
                if(el[6]!="n" and t==lengthPath-1):
                    f.write("initially "+el[6:el.rfind(",")]+".\n")

            elif(el[0]=="o" and el[7]!="n"):#occures and not noop
                comma_position=el.find(",")
                action= el[7               : comma_position]
                index = int(el[comma_position+1: -1])
                actionList.append(Action(action, index+i*10))
                os.system("echo '"+el+"'")
                actionList.sort(key=lambda x:x.index)
        
        f.close()
        

        actionsFile=open("output/actions.txt", "a")

        counter=0
        for act in actionList:
            actionsFile.write(str(counter)+"\t"+act.action+"\n")
            counter=counter+1
        
        actionsFile.write("----------------")
        actionsFile.write("----------------")
        actionsFile.close()

        #occurs(rotateFore(90),2)

    
    #holds(neg(has_col(orange,6,white)),10)
    #initially has_col(white, 2, green).
