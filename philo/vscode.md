<h1 align="center">Vscode</h1>

## Les Raccourcis

En maîtrisant les raccourcis, les développeurs peuvent significativement accélérer leur processus de développement, augmentant ainsi leur productivité.

Il n'est pas nécessaire de connaître tous les raccourcis, mais en apprendre certains est important.

Ci-dessous une liste triée de raccourcis utiles :

    Configuer et voir raccourci dispo :
        Ctrl + K + S : Raccourci Vscode
    Général :
        Ctrl + P  ou Ctrl + E: Ouvrir le fichier
        Ctrl + Shift + N : Ouvrir une nouvelle fenêtre
        Ctrl + \ : Basculer le panneau
        Ctrl + Shift + P : Vscode Commande:
        # pour chercher dans le code

    Édition :
        Ctrl + D : Ajoute à la sélection la prochaine itération de la sélection
        Ctrl + Z : Annuler
        Ctrl + Shift + Z : Rétablir
        Ctrl + X : Couper la sélection
        Ctrl + C : Copier la sélection
        Ctrl + V : Coller
        Ctrl + Shift + K : Supprimer la ligne
        Ctrl + ] ou [ : indentation droite gauche
        Ctrl + L : Sélectionne la ligne
        Ctrl + Entree : Insérer une ligne en dessous
        Shift + Puis-Flèche gauche/droite : sélection
        Shift + Alt + Puis-Flèche haut/bas : Multi-Curseur 
        Shift + Alt + Puis-Flèche gauche/droite : sélection par block
        Alt + Puis-Flèche haut/bas : Déplacer la ligne vers le haut/bas

    Navigation :
        Ctrl + G : Aller à la ligne
        Ctrl + \ : Diviser l'éditeur
        Ctrl + W : Fermer éditeur
		Ctrl + Tab : Basculer entre les tabs
        Ctrl + "0 - 9" : Changer de section vscode
        Ctrl + pageup pagedown : Pour basculer entre les éditeurs et les tabs
        Ctrl + Alt + - : Va à la position du curseur précedente
        Ctrl + Shift + - : Va à la position du curseur précedente
        Ctrl + tab : Naviguer entre les derniers onglets

    Recherche :
        Ctrl + F : Rechercher dans le fichier actif
        Ctrl + H : Remplacer dans le fichier actif : Entrée pour remplacer 1 par 1 : Ctrl + Alt + Entrée pour tout remplacer
		Ctrl + Shift + O : Ouvrir un fichier / Recherche par symbole dans le fichier actif
        Ctrl + Shift + F : Rechercher dans tous les fichiers
        Ctrl + Shift + H : Remplacer dans tous les fichiers : Entrée pour remplacer 1 par 1 : Ctrl + Alt + Entrée pour tous remplacer

    Navigation dans le code :
        Ctrl + Puis-Flèche gauche/droite : Déplacer le curseur par mot
        Ctrl + / : Commenter/décommenter la sélection

    Terminal intégré :
        Ctrl + ` : Ouvrir / Fermer le terminal intégré (si Focus sur le terminal, sinon met le focus sur le terminal)
		Ctrl + j : Ouvrir / Fermer le terminal intégré (peu importe ou se situe le focus)
        Ctrl + Shift + `: Ajouter session terminal intégré


    C/C++ IntelliSense
        Alt + O = Switch entre le .h et le fichier c / cpp


## .JSON

### Qu'est-ce que JSON ?

JSON (JavaScript Object Notation) est un format léger et lisible permettant de structurer des données sous forme d'objets. Il est utilisé pour :
- Personnaliser l'éditeur (settings.json)
- Configurer des outils et extensions
- Stocker des paramètres utilisateur
- Automatiser des tâches (tasks.json)
- Créer des snippets

### JSON dans VS Code

VS Code stocke ses préférences utilisateur et workspace dans des fichiers .json

Exemple de settings.json pour personnaliser l'éditeur:
		{
			"editor.fontSize": 16,
			"editor.tabSize": 4,
			"workbench.colorTheme": Visual Studio Dark"
		}
Le .json permet de modifier les paramètres sans passer par l'interface graphique.
Quelques settings intéressant:
		{
			"editor.wordWrap": "on", (Active le retour automatique à la ligne, évitant d'avoir des lignes trop longue qui dépasse l'écran)
			"files.autoSave": "afterDelay", (Sauvegarde après un délai d'inactivité. Par défaut : 1000ms)
			"window.zoomLevel" : 2, (Permet d'ajuster le zoom de l'interface)
		}

## Les Extensions

Les extensions sont le plus gros points fort de VScode, certaines sont obligatoires, d'autres vraiment utiles, en voici une liste :

- Avoir l'extension du language que vous codez est nécessaire ( ex : C/C++ Intelicense, )
- [gitlens](https://marketplace.visualstudio.com/items?itemName=eamodio.gitlens)

    Ajouter cette ligne dans le .json, désactive l'affichage du dernier commit sur chaque ligne modifiée

    	{
		    "gitlens.currentLine.enabled": false,
		}
- [githistory](https://marketplace.visualstudio.com/items?itemName=donjayamanne.githistory)
- [Todo Tree](https://marketplace.visualstudio.com/items?itemName=Gruntfuggly.todo-tree)
- [Remote - SSH](https://marketplace.visualstudio.com/items?itemName=ms-vscode-remote.remote-ssh) + [Doc](https://code.visualstudio.com/docs/remote/ssh)
- [Dev Container](https://marketplace.visualstudio.com/items?itemName=ms-vscode-remote.remote-containers) + [Doc](https://code.visualstudio.com/docs/devcontainers/containers)
- [Github Copilot](https://github.com/features/copilot) ( [What not to do](https://www.youtube.com/watch?v=2q0BoioYSxQ))
- [VSCode Neovim](https://marketplace.visualstudio.com/items?itemName=asvetliakov.vscode-neovim)
- [Rainbow Brackets](https://marketplace.visualstudio.com/items?itemName=2gua.rainbow-brackets)
- [Multi Command](https://marketplace.visualstudio.com/items?itemName=ryuta46.multi-command)

- Pour le fun [ici](https://marketplace.visualstudio.com/items?itemName=Tzanou.tamagotchi)

## Les Snippets

C / C++ IntelliSense par exemple intègre une bibilothèque de snippets que peut-être vous utilisez déjà.
Il existe aussi des extensions dediées, que vous pouvez chercher avec *@snippets* dans le market VScode.
Enfin il est possible d'en faire des personnalisées.

- [Video](https://www.youtube.com/watch?v=TGh2NpCIDlc) courte pour comprendre les snippets custom
- [Doc VScode](https://code.visualstudio.com/docs/editor/userdefinedsnippets)

## Les tasks

Outils très puissant qui permet l'automatisation de tâches, commandes au sein de VScode.

- [Doc VScode](https://code.visualstudio.com/docs/editor/tasks)
- Pour aller plus loin un [article](https://medium.com/@simonescigliuzzi/automating-multi-projects-execution-using-vscodes-tasks-10e102da5d96)

## Bonus

>Livre Make VScode Awesome [Ici](https://annas-archive.org/md5/8992f49c8c518bda4e8cc46bfc445e08)
