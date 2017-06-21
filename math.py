

#tokenize() => readOpen() => Parenthesis() => evaluate() => ...

#という関数の呼び出しが行われていて、
#なぜかtokenizeしている最中に、evaluateが走ることになってしまっています。

#1. tokenize()で字句解析を終わらせる
#2. evaluate()で評価する

#という大きな流れで書けるときれいですね。
#さらに、evaluate()を、

#- evaluateMultiplyDivide()
#- evaluatePlusMinus()
#- evaluateParenthesis()

#に分解すれば、とてもきれいにモジュール化できそうです。
#（現状のプログラムだと、readOpen()とかParenthesis()とかdividetimes()とかが複雑に絡まりあってしまっています。）

#このあたりは「慣れ」が必要なので、ふだんから心がけて書いてみるといいと思います！

#あと細かいことですが、aとかline2とかの変数名は、人が読んでもわかりやすいものにできるといいかなと思いました。

#おつかれさまでした！

def evaluate(tokens):
    answer = 0
    tokens.insert(0, {'type': 'PLUS'}) # Insert a dummy '+' token
    index = 1
    while index < len(tokens):
        if tokens[index]['type'] == 'NUMBER':
            if tokens[index - 1]['type'] == 'PLUS':
                answer += tokens[index]['number']
            elif tokens[index - 1]['type'] == 'MINUS':
                answer -= tokens[index]['number']
            else:
                print 'Invalid syntax'
        index += 1
    return answer

def devidetimes(line,index,number):
   while index < len(line) and (line[index] == '*' or line[index] == '/'):
        answer=number
        sig=index
        index +=1
        if line[index]=='-':
            answer *= -1
            index += 1
        if line[index]=="(":
            (number1,index) = Parenthesis(line,index)
        elif line[index].isdigit():
            number1 = 0
            while index < len(line) and line[index].isdigit():
                 number1 = number1 * 10 + int(line[index])
                 index += 1
        if line[sig]=='*':
                answer =(float)(answer)*number1
        elif line[sig]=='/':
                answer = (float)(answer)/number1

   return answer,index

def readNumber(line, index):
    number = 0
    while index < len(line) and line[index].isdigit():
        number = number * 10 + int(line[index])
        index += 1
    if index < len(line) and line[index] == '.':
        index += 1
        keta = 0.1
        while index < len(line) and line[index].isdigit():
            number += int(line[index]) * keta
            keta *= 0.1
            index += 1
    if index < len(line) and (line[index] == '*' or line[index] == '/'):
            (number,index) = devidetimes(line,index,number)
   
    token = {'type': 'NUMBER', 'number': number}
    return token, index


def readPlus(line, index):
    token = {'type': 'PLUS'}
    return token, index + 1


def readMinus(line, index):
    token = {'type': 'MINUS'}
    return token, index + 1

def Parenthesis(line,index):
    a=index
    opennum=1
    closenum=0
    index += 1
    while(opennum!=closenum):
       a += 1
       if line[a]=='(':
           opennum += 1
       if line[a] == ')':
           closenum += 1
    line2=line[index:a]
    tokenso = tokenize(line2)
    answero = evaluate(tokenso)
    return answero,a+1 

def readOpen(line, index):
    (number,index) = Parenthesis(line,index)
    if index-1==len(line)-1:
        line=line+'+0'
    if line[index] == '*' or line[index] == '/':
        (number,index) = devidetimes(line,index,number)
    token = {'type': 'NUMBER', 'number': number}
    return token ,index

def tokenize(line):
    tokens = []
    index = 0
    while index < len(line):
        if line[index].isdigit():
            (token, index) = readNumber(line, index)
        elif line[index] == '+':
            (token, index) = readPlus(line, index)
        elif line[index] == '-':
            (token, index) = readMinus(line, index)
        elif line[index] == '(':
            (token, index) = readOpen(line, index)
        else:
            print 'Invalid character found: ' + line[index]
            exit(1)
        tokens.append(token)
    return tokens

def test(line, expectedAnswer):
    tokens = tokenize(line)
    actualAnswer = evaluate(tokens)
    if abs(actualAnswer - expectedAnswer) < 1e-8:
        print "PASS! (%s = %f)" % (line, expectedAnswer)
    else:
        print "FAIL! (%s should be %f but was %f)" % (line, expectedAnswer, actualAnswer)


# Add more tests to this function :)
def runTest():
    print "==== Test started! ===="
    test("1+2", 3)
    test("1.0+2.1-3", 0.1)
    test("-9.0+28",19)
    test("0.7898346+8.435624-2",7.2254586)
    test("4*5+2-7",15)
    test("-8*3-7+4",-27)
    test("2.5*4",10)
    test("7*-8",-56)
    test("5/2",2.5)
    test("((2+5)*7)+3",52)
    test("(2+6*(3+4))-4",40)
    test("((3+4)*(4+4)-8)-8",40)
    test("(((3+4)*(4+4)-8)-8)/4",10)
    test("(((4-3)*(5*4)-8)-8)/4",1)
    print "==== Test finished! ====\n"

runTest()

while True:
    print '> ',
    line = raw_input()
    tokens = tokenize(line)
    answer = evaluate(tokens)
    print "answer = %f\n" % answer
