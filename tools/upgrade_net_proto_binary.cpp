// This is a script to upgrade "V0" network prototxts to the new format.
// Usage:
//    upgrade_net_proto_binary v0_net_proto_file_in net_proto_file_out

#include <cstring>
#include <fstream>  // NOLINT(readability/streams)
#include <iostream>  // NOLINT(readability/streams)
#include <string>

#include "caffe/caffe.hpp"
#include "caffe/util/io.hpp"
#include "caffe/util/upgrade_proto.hpp"

using std::ofstream;

using namespace caffe;  // NOLINT(build/namespaces)

int main(int argc, char** argv) {
<<<<<<< HEAD
  FLAGS_alsologtostderr = 1;  // Print output to stderr (while still logging)
=======
>>>>>>> 28a579eaf0668850705598b3075b8969f22226d9
  ::google::InitGoogleLogging(argv[0]);
  if (argc != 3) {
    LOG(ERROR) << "Usage: "
        << "upgrade_net_proto_binary v0_net_proto_file_in net_proto_file_out";
    return 1;
  }

  NetParameter net_param;
  string input_filename(argv[1]);
  if (!ReadProtoFromBinaryFile(input_filename, &net_param)) {
    LOG(ERROR) << "Failed to parse input binary file as NetParameter: "
               << input_filename;
    return 2;
  }
  bool need_upgrade = NetNeedsUpgrade(net_param);
  bool success = true;
  if (need_upgrade) {
    success = UpgradeNetAsNeeded(input_filename, &net_param);
    if (!success) {
      LOG(ERROR) << "Encountered error(s) while upgrading prototxt; "
                 << "see details above.";
    }
  } else {
<<<<<<< HEAD
    LOG(ERROR) << "File already in latest proto format: " << input_filename;
=======
    LOG(ERROR) << "File already in V1 proto format: " << argv[1];
>>>>>>> 28a579eaf0668850705598b3075b8969f22226d9
  }

  WriteProtoToBinaryFile(net_param, argv[2]);

<<<<<<< HEAD
  LOG(INFO) << "Wrote upgraded NetParameter binary proto to " << argv[2];
=======
  LOG(ERROR) << "Wrote upgraded NetParameter binary proto to " << argv[2];
>>>>>>> 28a579eaf0668850705598b3075b8969f22226d9
  return !success;
}
