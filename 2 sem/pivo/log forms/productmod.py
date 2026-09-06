from experta import Fact, KnowledgeEngine, Rule, NOT, MATCH


class Symptom(Fact):
    """Симптом пациента."""
    pass


class Diagnosis(Fact):
    """Диагноз."""
    pass


class DiagnosisEngine(KnowledgeEngine):
    @Rule(NOT(Symptom(name='температура')))
    def ask_temperature(self):
        value = input(
            "Температура (нормальная/повышенная/высокая/неизвестно): ").strip().lower()
        self.declare(Symptom(name='температура', value=value))

    @Rule(NOT(Symptom(name='кашель')))
    def ask_cough(self):
        value = input(
            "Кашель (нет/сухой/влажный/неизвестно): ").strip().lower()
        self.declare(Symptom(name='кашель', value=value))

    @Rule(NOT(Symptom(name='насморк')))
    def ask_cold(self):
        value = input("Насморк (нет/есть/неизвестно): ").strip().lower()
        self.declare(Symptom(name='насморк', value=value))

    @Rule(
        Symptom(name='температура', value='высокая'),
        Symptom(name='кашель', value='сухой') | Symptom(
            name='кашель', value='влажный'),
        Symptom(name='насморк', value='есть')
    )
    def flu(self):
        self.declare(Diagnosis(name='грипп'))
        print("Предположительный диагноз: грипп")

    @Rule(
        Symptom(name='температура', value='повышенная'),
        Symptom(name='кашель', value='сухой') | Symptom(
            name='кашель', value='влажный'),
        Symptom(name='насморк', value='есть')
    )
    def orz(self):
        self.declare(Diagnosis(name='ОРЗ'))
        print("Предположительный диагноз: ОРЗ")

    @Rule(
        Symptom(name='кашель', value='сухой') | Symptom(
            name='кашель', value='влажный'),
        Symptom(name='температура', value='нормальная') | Symptom(
            name='температура', value='неизвестно'),
        Symptom(name='насморк', value='нет') | Symptom(
            name='насморк', value='неизвестно'),
        NOT(Diagnosis(name='грипп')),
        NOT(Diagnosis(name='ОРЗ'))
    )
    def isolated_cough(self):
        self.declare(Diagnosis(name='изолированный_кашель'))
        print(
            "Есть кашель без других выраженных симптомов. Нужна дополнительная диагностика.")

    @Rule(
        Symptom(name='насморк', value='есть'),
        Symptom(name='температура', value='нормальная') | Symptom(
            name='температура', value='неизвестно'),
        Symptom(name='кашель', value='нет') | Symptom(
            name='кашель', value='неизвестно'),
        NOT(Diagnosis(name='грипп')),
        NOT(Diagnosis(name='ОРЗ')),
        NOT(Diagnosis(name='изолированный_кашель'))
    )
    def rhinitis(self):
        self.declare(Diagnosis(name='ринит'))
        print("Вероятно, лёгкий ринит (насморк без других симптомов).")

    @Rule(
        Symptom(name='температура', value='нормальная'),
        Symptom(name='кашель', value='нет'),
        Symptom(name='насморк', value='нет'),
        NOT(Diagnosis(name='грипп')),
        NOT(Diagnosis(name='ОРЗ')),
        NOT(Diagnosis(name='изолированный_кашель')),
        NOT(Diagnosis(name='ринит'))
    )
    def healthy(self):
        self.declare(Diagnosis(name='здоров'))
        print("Вероятно, вы здоровы.")

    @Rule(
        Symptom(name='температура', value=MATCH.t),
        Symptom(name='кашель', value=MATCH.c),
        Symptom(name='насморк', value=MATCH.n),
        NOT(Diagnosis())
    )
    def unknown(self, t, c, n):
        print("Не удалось поставить однозначный диагноз.")
        print(f"Введённые симптомы: температура={t}, кашель={c}, насморк={n}")


if __name__ == "__main__":
    engine = DiagnosisEngine()
    engine.reset()
    engine.run()
