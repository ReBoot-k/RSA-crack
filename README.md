# RSA взлом

### Минимальная версия: `C++17`

### Зависимости: `boosty`

## О проекте
Данный проект создан для решения заданий по RSA, а именно расшифровки сообщений, когда нам не доступны все параметры

![Схема работы RSA](https://github.com/ReBoot-k/RSA-crack/blob/C%2B%2B/media/c%D1%85%D0%B5%D0%BC%D0%B0.jpg)


Исходя из схемы работы, код высчитывает недостающие параметры, но только в следующих ситуациях:
- Отсутсвует `P` и/или `Q`, но есть `PHI` или `N`
- Отсуствует `N` или `PHI`, но есть `P` и `Q`
- Отсутвует `D`, но есть `E` и `PHI`
