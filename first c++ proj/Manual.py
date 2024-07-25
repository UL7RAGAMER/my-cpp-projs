#1
def lshift(l:list,n):
    for i in range(n):
        l.append(l.pop(0))
#2 
def ones(n1,n2):
    return n1 if n1%10>n2%10 else n2
#3  
def checkstr(s1,s2):
    return True if len(s1)==len(s2) else False
#4
def seris_gen(ini,fini):
    l=[]
    g = (fini - ini)/3
    while ini<fini+g : l.append(round(ini,3)) ;ini += g
    return l
#5
def fibnfac():
    menu = input("""Generate fibonacci for first 200 elements (Press 1)\nFind factorial of a number (Press 2)\n""")
    if menu == '1':
        def fib():
            cn=1
            t,pn=(0,0)
            while cn+ pn<200:
                print(cn+pn)
                t,pn = pn,cn
                cn += t
        fib()          
    elif menu == '2':
        def fact(n):
            if n == 0:
                return 1
            return n*fact(n-1)
        print(fact(8))
    else:
        print('Invalid option')
        return
#6
def filerep():
    
    with open('asd.txt','r') as f:
        data = f.read()
        data = data.replace(' ',',')
        with open("new.txt", 'a') as nf:
            nf.write(data)
#7      
def countinfile(file : str):
    count = 0
    with open(file, 'r') as f:
        data = f.read()
        data = data.split(' ')
        for i in data:
            if i == "to" or i == "the": 
                count+=1
        return count
    
#8  
def readndis(file : str):
    with open(file,'r') as f:
        n = len(f.readlines(-1))
        f.seek(0,0)
        for i in range(n):
            s = f.readline()
            if s[0] == 'a' or s[0] == 'e':
                print(s.strip())                
#9
def countfile(file:str):
    count = 0
    with open(file,'r') as f:
        for i in f.readlines(len(f.read()) + 1):
            data = f.readline()
            count += len(data.strip())
    return count  
#10
def savetofile(n):
    s :str = 'Rn,Name,Marks\n'
    for i in range(n):
        s+=input("Enter rn") + ","+ input("Enter name") + ',' + input('Enter marks')+'\n'
    with open('asd.txt','w') as f:
        f.write(s)