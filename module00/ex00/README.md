# Introduction à l'Encapsulation en C++

Ce module introduit un concept fondamental de la programmation orientée objet : **l'encapsulation**.  
À travers des exercices pratiques, vous apprendrez à protéger les données de vos classes, à contrôler l'accès aux attributs via des getters/setters, et à respecter les bonnes pratiques de conception orientée objet en C++.

---

# Table des matières

- [Exercice 00 – Divide and Conquer](#exercice-00--divide-and-conquer)
- [Exercice 01 – I Don’t Know What I’m Doing!](#exercice-01--i-dont-know-what-im-doing)
- [Bonuses](#bonuses)

---

# Exercice 00 – Divide and Conquer

## Objectif

**Encapsuler correctement les classes `Account` et `Bank**` pour qu’aucune action illogique ne puisse être effectuée depuis l’extérieur.  
Le code fourni représente un système bancaire où tout est accessible depuis l’extérieur, ce qui n’est pas sécurisé ni logique.

### Notions clés abordées

- **Encapsulation** : Regrouper les données (attributs) et les méthodes qui les manipulent dans une classe, tout en restreignant l’accès direct aux données.
- **Attributs privés** : Accessibles uniquement au sein de la classe.
- **Getters/Setters** : Méthodes publiques pour accéder ou modifier les attributs privés, avec validation si nécessaire.
- **Const-correctness** : Utilisation de méthodes `const` pour garantir que les getters ne modifient pas l’état de l’objet.

---

## Règles d’encapsulation à respecter


| Règle                                                                | Explication                                                                                      |
| -------------------------------------------------------------------- | ------------------------------------------------------------------------------------------------ |
| Les attributs doivent être privés.                                   | Empêche toute modification directe depuis l’extérieur.                                           |
| Utiliser des getters/setters si nécessaire.                          | Permet de contrôler l’accès et d’ajouter des validations.                                        |
| Les getters doivent être `const` et retourner des références.        | Évite les copies inutiles et garantit que la méthode ne modifie pas l’objet.                     |
| La banque doit prélever 5% de chaque dépôt sur les comptes clients.  | Logique métier à implémenter dans les méthodes de la classe `Bank`.                              |
| Les comptes ne doivent jamais avoir deux identifiants identiques.    | Géré via un mécanisme interne (ex. : incrémentation automatique ou vérification avant création). |
| La banque doit pouvoir créer/supprimer/modifier les comptes clients. | Méthodes publiques dans `Bank` pour gérer les comptes.                                           |
| Les prêts sont accordés dans la limite des fonds de la banque.       | Vérification des fonds disponibles avant d’accorder un prêt.                                     |


---

## Comparaison : Attributs publics vs privés

| Type   | Accès depuis l’extérieur | Sécurité |
| ------ | ------------------------ | -------- |
| Public | ✅ Oui                    | ❌ Faible |
| Privé  | ❌ Non                    | ✅ Élevée |

---

## Méthodes courantes pour l’encapsulation

### Getters

```cpp
class Account {
private:
    int balance;
public:
    int getBalance() const { return balance; } // Getter const
};
```

### Setters

```cpp
void setBalance(int newBalance) {
    if (newBalance >= 0) // Validation
        balance = newBalance;
}
```

---
# Exercice 01 – I Don’t Know What I’m Doing!

## Objectif

**Créer une classe `Graph` et une structure `Vector2**` pour représenter des points dans un espace 2D, puis afficher ces points sous forme d’un graphique ASCII.  
L’exercice vise à appliquer les principes d’encapsulation pour protéger les attributs `X` et `Y` de `Vector2`, ainsi que la taille et la liste des points dans `Graph`.

---

### Notions clés abordées

- **Encapsulation des attributs** : Décider si `X` et `Y` doivent être publics ou privés, et pourquoi.
- **Gestion des points** : Ajouter des points à un graphique et les afficher sous forme d’art ASCII.
- **Utilisation de `std::vector**` : Stocker dynamiquement les points dans `Graph`.
- **Affichage formaté** : Générer un graphique ASCII à partir des coordonnées des points.

---

## Structure des classes

### 1. `Vector2`

Représente un point en 2D avec des coordonnées `X` et `Y` (de type `float`).

```cpp
struct Vector2 {
private:
    float x;
    float y;
public:
    // Constructeur
    Vector2(float x, float y) : x(x), y(y) {}

    // Getters const
    float getX() const { return x; }
    float getY() const { return y; }

    // Setters (si nécessaire, avec validation)
    void setX(float newX) { x = newX; }
    void setY(float newY) { y = newY; }
};
```

**Pourquoi encapsuler ?**

- Empêcher la modification directe des coordonnées depuis l’extérieur.
- Permettre des validations (ex. : valeurs positives, limites de taille).

---

### 2. `Graph`

Contient une taille (`Vector2`) et une liste de points (`std::vector<Vector2>`).

```cpp
class Graph {
private:
    Vector2 size;
    std::vector<Vector2> points;
public:
    // Constructeur
    Graph(Vector2 size) : size(size) {}

    // Ajouter un point
    void addPoint(const Vector2& point) {
        if (point.getX() >= 0 && point.getX() <= size.getX() &&
            point.getY() >= 0 && point.getY() <= size.getY())
            points.push_back(point);
    }

    // Afficher le graphique en ASCII
    void display() const {
        // Logique d'affichage (voir exemple ci-dessous)
    }
};
```

---

## Exemple d’affichage ASCII attendu

Pour les points `(0,0)`, `(2,2)`, `(4,2)`, `(2,4)` et une taille de `5x5` :

```
> 5 . . . . . .
> 4 . . X . . .
> 3 . . . . . .
> 2 . . X . X .
> 1 . . . . . .
> 0 X . . . . .
>   0 1 2 3 4 5
```

**Logique d’affichage** :

1. Parcourir les lignes de haut en bas (de `size.y` à `0`).
2. Pour chaque ligne, parcourir les colonnes de gauche à droite (de `0` à `size.x`).
3. Afficher un `X` si un point existe à cette coordonnée, sinon `.`.

---

## Règles à respecter


| Règle                                                      | Explication                                                                           |
| ---------------------------------------------------------- | ------------------------------------------------------------------------------------- |
| `Vector2` doit contenir `x` et `y` (type `float`).         | Structure de base pour représenter un point.                                          |
| L’utilisateur doit pouvoir ajouter un `Vector2` à `Graph`. | Méthode publique `addPoint`.                                                          |
| Afficher le graphique en ASCII.                            | Méthode `display` pour générer la représentation visuelle.                            |
| Justifier les choix d’encapsulation.                       | Expliquer pourquoi `x`/`y` sont privés, et comment les getters/setters sont utilisés. |


---

# Bonuses

## Exercice 00 – Divide and Govern

### Objectifs supplémentaires


| Bonus                                                              | Explication                                                                 |
| ------------------------------------------------------------------ | --------------------------------------------------------------------------- |
| **Pas de méthodes autres que des getters `const` dans `Account`.** | `Account` devient une structure interne à `Bank`, avec un accès contrôlé.   |
| `**Account` doit être interne à `Bank`.**                          | Déclarer `Account` comme une classe imbriquée (`nested class`) dans `Bank`. |
| **Opérateur `[]` pour accéder à un compte par ID.**                | Surcharger `operator[]` dans `Bank` pour un accès direct.                   |
| **Gestion des erreurs via `throw`.**                               | Lever des exceptions pour les opérations invalides (ex. : ID inexistant).   |
| **Pas de boucle pour trouver un compte par ID.**                   | Utiliser une `std::map<int, Account>` pour un accès en O(1).                |


---

## Exercice 01 – What Am I Looking At?!

### Objectifs supplémentaires


| Bonus                                                       | Explication                                                                   |
| ----------------------------------------------------------- | ----------------------------------------------------------------------------- |
| **Générer une représentation graphique PNG du `Graph`.**    | Utiliser une bibliothèque comme `libpng` ou `Cairo` pour dessiner les points. |
| **Ajouter une fonctionnalité de ligne.**                    | Permettre de tracer des lignes entre deux points.                             |
| **Lire un fichier d’entrée contenant une liste de points.** | Parser un fichier texte pour charger les points dans `Graph`.                 |


---

### Exemple de fichier d’entrée

```
3 3
1 1
2 2
0 2
```

**Format** :

- Première ligne : taille du graphique (`x y`).
- Lignes suivantes : coordonnées des points (`x y`).


---

## Résumé des attentes


| Élément               | Exercice 00                    | Exercice 01                | Bonuses                           |
| --------------------- | ------------------------------ | -------------------------- | --------------------------------- |
| **Encapsulation**     | Classes `Bank`/`Account`       | Classes `Graph`/`Vector2`  | `Account` imbriquée, `operator[]` |
| **Fonctionnalités**   | Gestion des comptes/prêts      | Ajout/affichage de points  | PNG, lignes, fichier d’entrée     |
| **Gestion d’erreurs** | Exceptions pour les opérations | Validation des coordonnées | Exceptions pour le parsing        |
| **Affichage**         | Sortie console (solde, prêts)  | Graphique ASCII            | Image PNG                         |
