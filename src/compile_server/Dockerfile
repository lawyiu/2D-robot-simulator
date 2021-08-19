FROM emscripten/emsdk:2.0.27
RUN apt-get update && \
    apt-get install -y autoconf bison build-essential libssl-dev libyaml-dev libreadline6-dev zlib1g-dev \
    libncurses5-dev libffi-dev libgdbm6 libgdbm-dev libdb-dev
RUN git clone https://github.com/rbenv/ruby-build.git && cd ruby-build && PREFIX=./install ./install.sh && \
    ./install/bin/ruby-build 2.7.4 /usr/local/ruby-2.7.4 && cd ../ && rm -r ruby-build
RUN echo 'PATH=/usr/local/ruby-2.7.4/bin:$PATH' >> /etc/bash.bashrc
ENV PATH=/usr/local/ruby-2.7.4/bin:$PATH

RUN chown emscripten:emscripten /src

USER emscripten

RUN mkdir -p /src/headers /src/compile_dir

WORKDIR /src/headers
COPY --chown=emscripten:emscripten Arduino.h Arduino.tcc export.hpp pinDirection.hpp ./

WORKDIR /src
COPY --chown=emscripten:emscripten compile_server/Gemfile compile_server/Gemfile.lock ./
RUN bundle config set --local path 'vendor/bundle' && bundle config set --local without 'development test' && bundle install
COPY --chown=emscripten:emscripten compile_server/server.rb compile_server/config.ru compile_server/start.sh ./

CMD [ "./start.sh" ]
