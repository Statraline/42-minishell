*This project has been created as part of the 42 curriculum by srichard, remusung.*
![Langage](https://img.shields.io/badge/Language-C-blue)
![Système](https://img.shields.io/badge/System-UNIX-black)
![Statut](https://img.shields.io/badge/Status-Finished-success)
# Minishell

## Description

Minishell est un projet de reproduction d’un shell Unix. L’objectif du projet est de comprendre le fonctionnement interne d’un terminal en reconstruisant les etapes essentielles d’execution d’une commande : lecture de l’entree utilisateur, analyse syntaxique, expansion des variables, redirections, pipes, execution des commandes externes et gestion des built-ins.

La logique appliquee dans ce projet suit un pipeline precis :
- le **lexer** decoupe la ligne de commande en tokens pour isoler les mots, les operateurs et les redirections ;
- le **parser** transforme cette suite de tokens en structure logique afin de gerer correctement les priorites entre `|`, `&&`, `||`, les redirections et les subshells ;
- l’**expander** traite les variables d’environnement et `$?`, en respectant le comportement des quotes simples et doubles ;
- l’**execution** distingue les commandes externes et les built-ins, applique les redirections, gere les pipes et lance les processus enfants avec `fork` / `execve` ;
- la **gestion des signaux** permet de conserver un comportement proche d’un shell interactif classique, notamment avec `Ctrl-C`, `Ctrl-D` et `Ctrl-\\`.
Le projet utilise egalement une gestion interne de l’environnement, des heredocs, des redirections et du wildcard afin de se rapprocher du comportement d’un vrai shell.

## Instructions
**1. Compilation**
Le projet se compile avec `make` depuis la racine du depot.
```
make
```
**2. Usage**
Utiliser minishell comme un shell classique en lui transmettant des commandes. 

## Ressources
**Bibliographie** 
- [Qu'est-ce qu'un shell](https://www.lenovo.com/fr/fr/glossary/shell/?orgRef=https%253A%252F%252Fwww.google.com%252F): A quick-reading article to understand technically what is "shell" and how it's work. 
- [CS 134 OS—4.1 Shell](https://youtu.be/xCySbqj9BKI?si=Bo8iQq01IHnUCdpD): A video resuming the life circle of Shell.
- [Minishell Map](https://docs.google.com/spreadsheets/d/1uJHQu0VPsjjBkR4hxOeCMEt3AOM1Hp_SmUzPFhAH-nA/edit?usp=sharing) : An exhaustive list of Shell expected behaviour.
- [Ecriture d'un shell](https://segfault42.github.io/posts/minishell/) : Documentation on how to write a shell.
- [Mes conseils si je devais recommencer minishell](https://medium.com/@mostafa.omrane/mes-conseils-si-je-devais-recommencer-minishell-a9783c51ba1b) : Conseil d'organisation et notions sur le projet.
- [Minishell/builtins](https://mjose-portfolio.github.io/pages/minishellbuiltins.html).
- [why are some things shell builtins?](https://www.youtube.com/watch?v=p_KKDHJhi7A).
- [Terminal vs. Bash vs. Command line vs. Prompt](https://www.youtube.com/watch?v=hMSByvFHOro).
- [Shell Program Explained](https://www.youtube.com/watch?v=ubt-UjcQUYg&list=PL2POs8ZJ4I2JJK3lICRW0b-L2y9mLiDmU&index=2).
- [Let's build a super simple shell in C](https://www.youtube.com/watch?v=yTR00r8vBH8&list=PL2POs8ZJ4I2JJK3lICRW0b-L2y9mLiDmU&index=5).
- [Let's Write a Simple Shell in C!](https://www.youtube.com/watch?v=YMEHrXSsdo0).
- [Sending and Handling Signals in C (kill, signal, sigaction)](https://www.youtube.com/watch?v=83M5-NPDeWs&list=PL7_TuD9ZDMhg5uLHLyd8em13XBKfjzCzR).
- [Signals: Make Ctrl+C Do Anything You Want](https://www.youtube.com/watch?v=m6WXrC9Mxzo).
- [MiniShell](https://www.youtube.com/watch?v=wz0FslAzWn8).
- [Minishell: Building a mini-bash (a @42 project)](https://m4nnb3ll.medium.com/minishell-building-a-mini-bash-a-42-project-b55a10598218).
- [Understand Minishell](https://42-cursus.gitbook.io/guide/3-rank-03/minishell/understand-minishell).
- [ Writing a bash-like shell in C ](https://www.alimnaqvi.com/blog/minishell).
- [MInishell](https://github.com/facetint/minishell).
- Groupe Discorde minishell et peers-to-peers qui a ete d'une grande aide pour le debug final.

**Usage de l'IA**
- Vulgarisation de nouvelles notions complexes.
- Comprehension de nouvelles fonctions autorisees avec des manuels peu explicites.
- Creation de testeur pour verifier la robustesse du code.
