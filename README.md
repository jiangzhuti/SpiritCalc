# SpiritCalc

ebnf:
```
expr ::= term { (+|-) term }*
term ::= factor { (*|/) factor }*
factor ::= ( expr )
     | NUM

```

```
[jzt@lq-rog SpiritCalc]$ g++ -o calc main.cpp 
[jzt@lq-rog SpiritCalc]$ ./calc 
3+5+2/(1-3*(2+6/2))
7.85714
2+/3
failed to parse at: "+/3"
q
```
