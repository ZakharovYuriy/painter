# Создать образ на основе базового слоя nginx 
FROM nginx

# Выполнить установку зависимостей внутри контейнера.
RUN apt update && \
    apt install -y \
      cmake\
      gcc\
      g++
      
#создаем папку сборки
RUN mkdir -p /app/build

# Скопировать файлы проекта внутрь контейнера
COPY ./src /app/src
COPY CMakeLists.txt /app/

# Сборка проекта
RUN cd /app/build && \
    cmake -DCMAKE_BUILD_TYPE=Release .. && \
    cmake --build .

# Копирование дополнительных файлов
COPY ./bash /app/bash
COPY ./tests /app/tests

# Делаем фалы исполняемыми
RUN chmod +x /app/bash/start_program.sh
RUN chmod +x /app/bin/html_paint


# Запускаем
ENTRYPOINT ["/app/bash/start_program.sh"]
