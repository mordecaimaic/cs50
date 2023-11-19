class Jar:
    def __init__(self, capacity=12):
        if capacity < 0:
            raise ValueError("Capacaity should greater than 0")
        self._capacity = capacity
        self._size = 0

    def __str__(self):
        return (self._size * '🍪')

    def deposit(self, n):
        self._size += n
        if self._size > self._capacity:
            raise ValueError("Add too much cookies!")

    def withdraw(self, n):
        self._size -= n
        if self._size < 0:
            raise ValueError("No more cookies can be removed")

    @property
    def capacity(self):
        return self._capacity

    @property
    def size(self):
        return self._size

def main():

    cookie_jar = Jar()
    cookie_jar.deposit(5)
    # cookie_jar.withdraw(2)
    print(cookie_jar)

if __name__ == "__main__":
    main()