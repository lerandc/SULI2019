import MDAnalysis as mda
import MDAnalysis.analysis.rdf as RDF
import numpy as np
import matplotlib.pyplot as plt

u = mda.Universe("/home/lerandc/Downloads/dump_Ta", topology_format='LAMMPSDUMP')

ag = u.atoms
pos_hold = np.copy(u.atoms.positions)
rem_z = np.ones(pos_hold.shape)
rem_y = np.ones(pos_hold.shape)
rem_x = np.ones(pos_hold.shape)

print(rem_z.shape)
rem_z[:,2] = 0
rem_y[:,1] = 0
rem_x[:,0] = 0

ag.positions = pos_hold*rem_z
# Calculate 3D rdf
Ta_3D_rdf = RDF.InterRDF(ag,ag,range=[0.0,20.0],verbose=True)
Ta_3D_rdf.run()
print('3D rdf calculated.')

#Calculate 2D rdfs
# print(ag.positions[0])
# # Ta_2D_z_rdf = RDF.InterRDF(ag,ag,range=[0.0,20.0],verbose=True)
# # Ta_2D_z_rdf.run()
# # print('2D rdf in Z calculated.')

# ag.positions = pos_hold*rem_y
# print(ag.positions[0])
# # Ta_2D_y_rdf = RDF.InterRDF(ag,ag,range=[0.0,20.0],verbose=True)
# # Ta_2D_y_rdf.run()
# # print('2D rdf in Y calculated.')

# ag.positions = pos_hold*rem_x
# print(ag.positions[0])
# Ta_2D_x_rdf = RDF.InterRDF(ag,ag,range=[0.0,20.0],verbose=True)
# Ta_2D_x_rdf.run()
# print('2D rdf in X calculated.')

# x_dict = {'bins':Ta_2D_x_rdf.bins,'rdf':Ta_2D_x_rdf.rdf}
# y_dict = {'bins':Ta_2D_y_rdf.bins,'rdf':Ta_2D_y_rdf.rdf}
# z_dict = {'bins':Ta_2D_z_rdf.bins,'rdf':Ta_2D_z_rdf.rdf}
dict_3D = {'bins':Ta_3D_rdf.bins,'rdf':Ta_3D_rdf.rdf}

# np.save('Ta_2Dx',x_dict)
# np.save('Ta_2Dy',y_dict)
# np.save('Ta_2Dz',z_dict)
np.save('Ta_2D_z_v2',dict_3D)

# fig,((ax11,ax12),(ax21,ax22)) = plt.subplots(2,2)

ax11.plot(Ta_3D_rdf.bins[1:],Ta_3D_rdf.rdf[1:])
# ax12.plot(Ta_2D_z_rdf.bins[1:],Ta_2D_z_rdf.rdf[1:])
# ax21.plot(Ta_2D_y_rdf.bins[1:],Ta_2D_y_rdf.rdf[1:])
# ax22.plot(Ta_2D_x_rdf.bins[1:],Ta_2D_x_rdf.rdf[1:])
# plt.show()