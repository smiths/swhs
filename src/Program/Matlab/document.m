opts.format = 'latex';
opts.evalCode = false;
opts.outputDir = '\';
publish('main.m', opts);
publish('load_params', opts);
publish('temperature1.m', opts);
publish('temperature2.m', opts);
publish('temperature3.m', opts);
publish('event1.m', opts);
publish('event2.m', opts);
publish('energy1.m', opts);
publish('energy2.m', opts);
publish('energy3.m', opts);
publish('plots.m', opts);
publish('output.m', opts);