#Opdracht 7_3 Two-dimensional lists
studentencijfers = [ [95, 92, 86],[66, 75, 54],[89, 72, 100],[34, 0, 0] ]
def gemiddelde_per_student(studentencijfers):
    gemiddelde = []
    for student in studentencijfers:
        gemiddelde.append(sum(student) / len(student))
    return gemiddelde

def gemiddelde_van_alle_studenten(studentencijfers):
    res = gemiddelde_per_student(studentencijfers)
    return sum(res) / len(res)

print(gemiddelde_per_student(studentencijfers))
print(gemiddelde_van_alle_studenten(studentencijfers))