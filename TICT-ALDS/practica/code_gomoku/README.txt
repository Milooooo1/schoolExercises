Wat heb ik gedaan om het MCTS algoritme te verbeteren?
    Ik heb een functie gemaakt die voor mij de "slimme" moves zoekt. Volgens mijn tactiek
    zijn de slimme moves, moves waar je jouw steen naast een al liggende steen legt of
    wanneer je jou steen in een radius van n rond je laatste move legt. N is in mijn geval 5, ik wil hier 
    nog mee experimenteren
    
    Ik heb ook gexperimenteerd met verschillende constantes voor de UCT en mij ingelezen in alternatieven/ verbeteringen
    voor de UCT formule. 
    Wat de constante betreft is mijn redenatie dat een hoge C beter werkt, bij een hoge C exploit je meer, 
    je gaat dus meer in op bepaalde nodes. Je gaat nu dus door op zetten die je eerder probeerd.
    Uit alle tests die je in winratiolog.txt kan zien ben ik gegaan voor een constante van 32
    
    Ik heb gekeken naar RAVE en P(rediction)UCT. RAVE gaat uit van het "all moves as first" heuristiek. 
    RAVE 'deelt' ook informatie tussen nodes. Ik ga dit echter niet implementeren, een artikel genaamd 
    "Enhancing Upper Confidence Bounds for Trees with Temporal Difference Values" van Tom Voopivec en Branko Ster
    heeft namelijk de normale UCT formule al getest ten opzichte van RAVE en een paar andere formules, je kan hier echter zien
    dat RAVE alleen een grote performance increase geeft als je maar 50 - 100 iteraties per speler kan doen. Mijn MCTS doet tussen de 300
    en 1000 iteraties. 
    Wat PUCT betreft heb ik dit al enigsinds gedaan door alleen de moves waarvan ik denk dat deze 'slim' zijn te geven, puct gaat namelijk
    uit van een prediction qua wat een slimme move is.     
    
    
    
In winratiolog.txt is een log te zien van alle games die ik heb gesimuleerd om te 
bepalen of een bepaalde waarde of tactiek de moeite waard is om te bestuderen. 





Persoonlijke TODO lijst:
Kopieer niet steeds het hele bord
    Zet hier de moves op en haal deze er af voor elke child. 
Bereken niet steeds alle mogelijke moves voor het bord
    Doe dit een keer en haal hier de laatste move vanaf. 
    


Bronnen:
https://www.cs.utexas.edu/~pstone/Courses/394Rspring13/resources/mcrave.pdf
https://www.researchgate.net/figure/Performance-against-UCT-on-Gomoku-7x7-when-increasing-the-number-of-MCTS-iterations-per_fig2_286733609
https://www.chessprogramming.org/UCT
https://en.wikipedia.org/wiki/Monte_Carlo_tree_search#Improvements
https://pure.uvt.nl/ws/portalfiles/portal/13692454/bakkes_cig2016_paper_10.pdf