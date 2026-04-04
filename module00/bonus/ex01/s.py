import numpy as np

# Paramètres du repère
max_coord = 100

# Génération des coordonnées pour un smiley avec une bouche souriante
# Visage (cercle)
theta = np.linspace(0, 2*np.pi, 200)
x_cercle = 50 + 30 * np.cos(theta)
y_cercle = 50 + 30 * np.sin(theta)

# Yeux (deux petits cercles)
theta_yeux = np.linspace(0, 2*np.pi, 50)
x_oeil_gauche = 40 + 5 * np.cos(theta_yeux)
y_oeil_gauche = 60 + 5 * np.sin(theta_yeux)
x_oeil_droit = 60 + 5 * np.cos(theta_yeux)
y_oeil_droit = 60 + 5 * np.sin(theta_yeux)

# Bouche souriante (arc de cercle vers le haut)
theta_bouche_sourire = np.linspace(np.pi/6, 5*np.pi/6, 150)
x_bouche_sourire = 49 - 25 * np.cos(theta_bouche_sourire)
y_bouche_sourire = 49 - 25 * np.sin(theta_bouche_sourire) + 10

# Combinaison de toutes les coordonnées
x_tot_sourire = np.concatenate([x_cercle, x_oeil_gauche, x_oeil_droit, x_bouche_sourire])
y_tot_sourire = np.concatenate([y_cercle, y_oeil_gauche, y_oeil_droit, y_bouche_sourire])

# Sauvegarde dans un fichier pour un smiley avec une bouche souriante
fichier_sourire = "smiley_coords_sourire.txt"
with open(fichier_sourire, 'w') as f:
    for x, y in zip(x_tot_sourire, y_tot_sourire):
        f.write(f"{int(x)} {int(y)}\n")

print(f"Fichier généré : {fichier_sourire}")