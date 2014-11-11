require 'orocos'
require 'vizkit'
Orocos::CORBA.name_service = "127.0.0.1"
Orocos.initialize

Orocos.run 'camera_v4l' do |*_|
	camera = Orocos::TaskContext.get 'v4l_cam'
	camera.camera_id = 1
	camera.configure
	camera.start
	frame = Vizkit.display camera.frame 
	Vizkit.exec
end

