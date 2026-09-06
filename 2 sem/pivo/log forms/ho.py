from kanren import Relation, facts, run, var, conde
student_exam = Relation()
subject_type = Relation()
grade_category = Relation()
student_course = Relation()

facts(student_exam,
      ("Алексей", "Математика",        "5"),
      ("Алексей", "Физика",            "5"),
      ("Алексей", "Программирование",  "4"),
      ("Алексей", "История",           "зачёт"),

      ("Антон",   "Математика",        "4"),
      ("Антон",   "Физика",            "4"),
      ("Антон",   "Программирование",  "4"),
      ("Антон",   "История",           "зачёт"),

      ("Дмитрий", "Математика",        "3"),
      ("Дмитрий", "Физика",            "4"),
      ("Дмитрий", "Программирование",  "3"),
      ("Дмитрий", "История",           "зачёт"),

      ("Елена",   "Математика",        "2"),
      ("Елена",   "Физика",            "3"),
      ("Елена",   "Программирование",  "2"),
      ("Елена",   "История",           "незачёт"),

      ("Сергей",  "Математика",        "5"),
      ("Сергей",  "Физика",            "3"),
      ("Сергей",  "Программирование",  "5"),
      ("Сергей",  "История",           "зачёт"),
      )
facts(subject_type,
      ("Математика",       "экзамен"),
      ("Физика",           "экзамен"),
      ("Программирование", "экзамен"),
      ("История",          "зачёт"),
      )
facts(grade_category,
      ("5", "отлично"),
      ("4", "хорошо"),
      ("3", "удовл"),
      ("2", "неудовл"),
      )

facts(student_course,
      ("Алексей", "Информатика"),
      ("Антон",   "Информатика"),
      ("Дмитрий", "Математика"),
      ("Елена",   "Математика"),
      ("Сергей",  "Информатика"),
      )


def has_grade(student, subject, category):
    grade = var()
    return conde(
        (
            subject_type(subject, "экзамен"),
            student_exam(student, subject, grade),
            grade_category(grade, category),
        ),
    )


def passed_credit(student, subject):
    return conde(
        (
            subject_type(subject, "зачёт"),
            student_exam(student, subject, "зачёт"),
        ),
    )


def high_performer(student):
    subject = var()
    return conde(
        (has_grade(student, subject, "отлично"),),
    )


def average_performer(student):
    subject = var()
    return conde(
        (has_grade(student, subject, "хорошо"),),
    )


def low_performer(student):
    subject = var()
    return conde(
        (has_grade(student, subject, "неудовл"),),
        (
            subject_type(subject, "зачёт"),
            student_exam(student, subject, "незачёт"),
        ),
    )


x = var()
s = var()
subj = var()
cat = var()
print("1. Какие предметы Алексей сдал на отлично?")
print(run(0, x, has_grade("Алексей", x, "отлично")))

print("\n2. У каких студентов есть хотя бы одна отличная оценка?")
print(tuple(set(run(0, s, high_performer(s)))))

print("\n3. У каких студентов низкая успеваемость?")
print(tuple(set(run(0, s, low_performer(s)))))

print("\n4. По каким предметам у Елены низкие результаты?")
bad_subj = var()
print(run(0, bad_subj,
          conde(
              (has_grade("Елена", bad_subj, "неудовл"),),
              (subject_type(bad_subj, "зачёт"), student_exam(
                  "Елена", bad_subj, "незачёт"),),
          )
          ))

print("\n5. Какие студенты направления «Информатика» имеют хорошие оценки?")
print(tuple(set(run(0, s, student_course(s, "Информатика"), average_performer(s)))))

print("\n6. Какие оценки получил Дмитрий и какова их категория?")
print(run(0, (subj, cat), has_grade("Дмитрий", subj, cat)))

print("\n7. Кто сдал зачёт по Истории?")
print(run(0, s, passed_credit(s, "История")))
