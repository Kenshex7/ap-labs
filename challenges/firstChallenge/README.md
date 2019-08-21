First Code Challenge
====================

Given a string, find the length of the longest substring without repeating characters.

Example 1
---------
```
Input: "abcabcbb"
Output: 3
```

**Explanation:** The answer is `abc`, with the length of 3.


Example 2:
----------
```
Input: "bbbbb"
Output: 1
```

**Explanation:** The answer is `b`, with the length of 1.


Example 3:
----------
```
Input: "pwwkew"
Output: 3
```
**Explanation:** The answer is `wke`, with the length of 3.
Note that the answer must be a substring, `pwke` is a subsequence and not a substring.


Build Requirements
------------------
```
Python 3
Any bash or cmd
```


How to build
------------
Copy this code to a text file with the extension .py
```
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
```

How to Run
----------
```
execute the .py file with python in any cmd or bash
```


Submission Requirements
-----------------------
- Use the programming language of your choice
- Fill the [Build Requirements](#build-requirements), [How to build](#how-to-Build) and [How to Run](#how-to-run) sections on this `README.md` file.
- You can use an online IDE for testing your code (e.g. https://ideone.com/)
- Submit your solution with:
```
make submit
```
