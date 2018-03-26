# Mekatronikjunta
Här samlar vi alla mekatronikjunta hacken!

## Git Know How!
För att kolla hur ditt local repo status är emot master repo, kör
```
git status
```

För att vara up-to-date med de senaste ändringar i repo, ta ner alla ändringar med
```
git pull
```

Lös alla mergeconflicts som uppstår.

## Lägg till en fil på master repo
```
git add < file-du-vill-lägg till>
git commit -a -m "Skriv något så vi fattar vad som hänt"
git push
```
Nu ligger filen uppe udner mekatronikjunta!

## Pusha ändringar ifrån dina lokala filer till master
```
git commit -a -m "Skriv något så vi fattar vad som hänt"
git push
```

## Köra LedTowers
För att kunna köra LedTowers måste du checka ut submoduler
```
git submodule update --init 
```

 Öppna nu Arduion IDE. Under Preferences -> Sketchbook location skriver du
 *<path-to-git-repo-on-local-machine>*\mekatronikjunta\Mars