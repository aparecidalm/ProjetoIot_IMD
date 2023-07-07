FROM nodered/node-red
RUN npm i node-red-node-email
RUN npm i node-red-dashboard
RUN npm i node-red-node-random
RUN npm i node-red-contrib-moment