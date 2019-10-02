txt = input("Write letters\n");
wrd=0
prevlet=[]
for let in txt:
	if let in prevlet :
		if wrd<len(prevlet):
			wrd=len(prevlet)
		prevlet=prevlet[prevlet.index(let)+1:]
		prevlet.append(let)
	else:
		prevlet.append(let)
if wrd<len(prevlet):
			wrd=len(prevlet)
print("The longest word have "+str(wrd)+" characters")