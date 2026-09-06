from experta import Fact, KnowledgeEngine, Rule, NOT, MATCH


class Symptom(Fact):
    """Типы ошибок."""
    pass


class Diagnosis(Fact):
    """Програмнная ошибка."""
    pass


class DiagnosisEngine(KnowledgeEngine):
    @Rule(NOT(Symptom(name='падает')))
    def ask_temperature(self):
        value = input(
            "Падает программа (Да/Нет)): ").strip().lower()
        self.declare(Symptom(name='падает', value=value))

    @Rule(NOT(Symptom(name='Зависает ли программа')))
    def ask_cough(self):
        value = input(
            "зависает ли программа (Да/Нет): ").strip().lower()
        self.declare(Symptom(name='Зависает ли программа', value=value))

    @Rule(NOT(Symptom(name='Программа дает неверный результат')))
    def ask_cold(self):
        value = input(
            "Программа дает неверный результат (Да/Нет): ").strip().lower()
        self.declare(
            Symptom(name='Программа дает неверный результат', value=value))

    @Rule(
        Symptom(name='падает', value='да'),
        Symptom(name='Зависает ли программа', value='да'),
        Symptom(name='Программа дает неверный результат', value='нет')
    )
    def flu(self):
        self.declare(Diagnosis(name='критическая ошибка памяти'))
        print("Предположительный тип: критическая ошибка памяти")

    @Rule(
        Symptom(name='падает', value='нет'),
        Symptom(name='Зависает ли программа', value='да'),
        Symptom(name='Программа дает неверный результат', value='нет')
    )
    def orz(self):
        self.declare(Diagnosis(name='Бесконечный цикл или deadlock'))
        print("Предположительный тип: Бесконечный цикл или deadlock")

    @Rule(
        Symptom(name='падает', value='нет'),
        Symptom(name='Зависает ли программа', value='нет'),
        Symptom(name='Программа дает неверный результат', value='да'),
    )
    def isolated_cough(self):
        self.declare(Diagnosis(name='Логическая ошибка алгоритма'))
        print("Предположительный тип: Логгическая ошибка алгоритма")

    @Rule(
        Symptom(name='падает', value='да'),
        Symptom(name='Зависает ли программа', value='да'),
        Symptom(name='Программа дает неверный результат', value='да'),

    )
    def rhinitis(self):
        self.declare(
            Diagnosis(name='Синхронизационная ошибка в многопоточности.'))
        print("Вероятно,  Синхронизационная ошибка в многопоточности.")

    @Rule(
        Symptom(name='падает', value='да'),
        Symptom(name='Зависает ли программа', value='нет'),
        Symptom(name='Программа дает неверный результат', value='да'),
    )
    def healthy(self):
        self.declare(
            Diagnosis(name='Необработанное исключение с неверными данными'))
        print("Вероятно, Необработанное исключение с неверными данными.")

    @Rule(
        Symptom(name='падает', value='нет'),
        Symptom(name='Зависает ли программа', value='да'),
        Symptom(name='Программа дает неверный результат', value='да'),

    )
    def unknown(self, t, c, n):
        self.declare(
            Diagnosis(name='Тайм-аут ожидания с накопленной логической ошибкой.'))
        print("Вероятно, Тайм-аут ожидания с накопленной логической ошибкой.")

    @Rule(
        Symptom(name='падает', value=MATCH.t),
        Symptom(name='Зависает ли программа', value=MATCH.c),
        Symptom(name='Программа неверный результат', value=MATCH.n),
        NOT(Diagnosis())
    )
    def unknown(self, t, c, n):
        print("Не удалось опеределить тип.")

    @Rule(
        Symptom(name='падает', value='нет'),
        Symptom(name='Зависает ли программа', value='да'),
        Symptom(name='Программа дает неверный результат', value='да'),
    )
    def new_case(self):
        print("Предположительный тип: Зависание с логической ошибкой")


if __name__ == "__main__":
    engine = DiagnosisEngine()
    engine.reset()
    engine.run()
