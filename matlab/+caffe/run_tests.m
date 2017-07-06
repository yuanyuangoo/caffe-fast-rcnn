function results = run_tests()
% results = run_tests()
%   run all tests in this caffe matlab wrapper package

% use CPU for testing
caffe.set_mode_cpu();

% reset caffe before testing
caffe.reset_all();

% put all test cases here
results = [...
  run(caffe.test.test_net) ...
<<<<<<< HEAD
  run(caffe.test.test_solver) ...
  run(caffe.test.test_io) ];
=======
  run(caffe.test.test_solver) ];
>>>>>>> 28a579eaf0668850705598b3075b8969f22226d9

% reset caffe after testing
caffe.reset_all();

end
