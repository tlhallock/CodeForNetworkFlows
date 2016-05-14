
inputFile = 'arcs.csv';
outputFile = 'mine.txt';
 
 
tmpFile = outputFile + '.tmp'
temp = open(tmpFile, 'w');

maxNode = 0;
numEdges = 0;

with open('arcs.csv','r') as f:
	for line in f:
		s = line.split(',');
		if len(s) < 5:
			continue
		numEdges = numEdges + 1;
		temp.write(s[1] + ' ' + s[2] + ' ' + s[4] + '\n');
		maxNode = max(maxNode, int(s[1]));
		maxNode = max(maxNode, int(s[2]));


temp.close();


f = open(tmpFile,'r')
temp = f.read()
f.close()

f = open(outputFile, 'w')
f.write(str(maxNode+1) + ' ' + str(numEdges) + '\n')
f.write(temp)
f.close()

