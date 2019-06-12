#include <iostream>
#include <string>
#include "H5Cpp.h"

int main (void){


	//creating file and dataspace
	H5::H5File file("test.h5", H5F_ACC_TRUNC);

	//working on attributes

	//write version major, minor attributes
	int maj_data[1] = {0};
	int min_data[1] = {1};
	hsize_t attr_dims[1] = {1};

	H5::DataSpace attr_dataspace(1,attr_dims);

	H5::Attribute maj_attr = file.createAttribute("version_major",H5::PredType::NATIVE_INT,attr_dataspace);
	H5::Attribute min_attr = file.createAttribute("version_minor",H5::PredType::NATIVE_INT,attr_dataspace);

	maj_attr.write(H5::PredType::NATIVE_INT, maj_data);
	min_attr.write(H5::PredType::NATIVE_INT, min_data);

	H5::Group umbrella(file.createGroup("/prismatic_simulation"));

	//initialize a 4D data set ala 4D-STEM
	H5::Group fourDim(umbrella.createGroup("4D_STEM"));
	hsize_t  dims[4] = {2,2,2,2};
	H5::DataSpace mspace1(4,dims);

	H5::DataSet dataset_4D = fourDim.createDataSet("data",H5::PredType::NATIVE_FLOAT, mspace1);

	//writing a dummy 4D data set
	{
		H5::DataSpace fspace1 = dataset_4D.getSpace();
		hsize_t offset[4];
		offset[0] = 0;
		offset[1] = 0;
		offset[2] = 0;
		offset[3] = 0;
		hsize_t dims1[4] = {1,1,2,2};
		fspace1.selectHyperslab(H5S_SELECT_SET, dims1, offset);

		float data2[9];
		for (auto i = 0; i < 9; i++) data2[i] = i+11.1;
		hsize_t dims2[4] = {1,1,2,2};
		H5::DataSpace mspace2(4,dims2);
		dataset_4D.write(data2, H5::PredType::NATIVE_FLOAT, mspace2,fspace1);

		H5::DataSpace fspace2 = dataset_4D.getSpace();
		hsize_t offset2[4];
		offset2[0] = 1;
		offset2[1] = 0;
		offset2[2] = 0;
		offset2[3] = 0;
		fspace2.selectHyperslab(H5S_SELECT_SET, dims1, offset2);

		for (auto i = 0; i < 9; i++) data2[i] = i+21.2;
		H5::DataSpace mspace3(4,dims2);
		dataset_4D.write(data2,H5::PredType::NATIVE_FLOAT, mspace3,fspace2);
	}

	//writing 4D data set dimensions
	//dim1
	{
		//create dimension data set
		hsize_t dim_attr_dims[1] = {2};
		H5::DataSpace dset_4D_dimSpace(1,dim_attr_dims);
		H5::DataSet dataset_4D_dim1 = fourDim.createDataSet("dim1",H5::PredType::NATIVE_FLOAT,dset_4D_dimSpace);

		H5::DataSpace dim1_4D_fspace = dataset_4D_dim1.getSpace();
		float dim1_data[2] = {0.0,2.5};
		dataset_4D_dim1.write(dim1_data,H5::PredType::NATIVE_FLOAT,dset_4D_dimSpace,dim1_4D_fspace);

		//write attributes for the dimension
		//set up str data space/type and di1 str buffer
		H5::DataSpace str_name_ds(H5S_SCALAR);
		H5::StrType strdatatype(H5::PredType::C_S1,256);

		const H5std_string dataset_4D_dim1_name_str("ay");
		H5::Attribute dataset_4D_dim1_name = dataset_4D_dim1.createAttribute("name",strdatatype,str_name_ds);
		dataset_4D_dim1_name.write(strdatatype, dataset_4D_dim1_name_str);


		const H5std_string dataset_4D_dim1_units_str("[n_m]");
		H5::Attribute dataset_4D_dim1_units = dataset_4D_dim1.createAttribute("units",strdatatype,str_name_ds);
		dataset_4D_dim1_units.write(strdatatype, dataset_4D_dim1_units_str);
	}

	//dim2
	{
		hsize_t dim_attr_dims[1] = {2};
		H5::DataSpace dset_4D_dimSpace(1,dim_attr_dims);
		H5::DataSet dataset_4D_dim2 = fourDim.createDataSet("dim2",H5::PredType::NATIVE_FLOAT,dset_4D_dimSpace);
		
		H5::DataSpace dim2_4D_fspace = dataset_4D_dim2.getSpace();
		float dim2_data[2] = {0.0,2.5};
		dataset_4D_dim2.write(dim2_data,H5::PredType::NATIVE_FLOAT,dset_4D_dimSpace,dim2_4D_fspace);
		
		//set up str data space/type and di1 str buffer
		H5::DataSpace str_name_ds(H5S_SCALAR);
		H5::StrType strdatatype(H5::PredType::C_S1,256);

		const H5std_string dataset_4D_dim2_name_str("ax");
		H5::Attribute dataset_4D_dim2_name = dataset_4D_dim2.createAttribute("name",strdatatype,str_name_ds);
		dataset_4D_dim2_name.write(strdatatype, dataset_4D_dim2_name_str);


		const H5std_string dataset_4D_dim2_units_str("[n_m]");
		H5::Attribute dataset_4D_dim2_units = dataset_4D_dim2.createAttribute("units",strdatatype,str_name_ds);
		dataset_4D_dim2_units.write(strdatatype, dataset_4D_dim2_units_str);
	}
	
	//dim3
	{
		hsize_t dim_attr_dims[1] = {2};
		H5::DataSpace dset_4D_dimSpace(1,dim_attr_dims);
		H5::DataSet dataset_4D_dim3 = fourDim.createDataSet("dim3",H5::PredType::NATIVE_FLOAT,dset_4D_dimSpace);

		H5::DataSpace dim3_4D_fspace = dataset_4D_dim3.getSpace();
		float dim3_data[2] = {-1.5,1.5};
		dataset_4D_dim3.write(dim3_data,H5::PredType::NATIVE_FLOAT,dset_4D_dimSpace,dim3_4D_fspace);

		//set up str data space/type and di1 str buffer
		H5::DataSpace str_name_ds(H5S_SCALAR);
		H5::StrType strdatatype(H5::PredType::C_S1,256);

		const H5std_string dataset_4D_dim3_name_str("qy");
		H5::Attribute dataset_4D_dim3_name = dataset_4D_dim3.createAttribute("name",strdatatype,str_name_ds);
		dataset_4D_dim3_name.write(strdatatype, dataset_4D_dim3_name_str);


		const H5std_string dataset_4D_dim3_units_str("[n_m^-1]");
		H5::Attribute dataset_4D_dim3_units = dataset_4D_dim3.createAttribute("units",strdatatype,str_name_ds);
		dataset_4D_dim3_units.write(strdatatype, dataset_4D_dim3_units_str);
	}

	//dim4
	{
		hsize_t dim_attr_dims[1] = {2};
		H5::DataSpace dset_4D_dimSpace(1,dim_attr_dims);
		H5::DataSet dataset_4D_dim4 = fourDim.createDataSet("dim4",H5::PredType::NATIVE_FLOAT,dset_4D_dimSpace);
		
		H5::DataSpace dim4_4D_fspace = dataset_4D_dim4.getSpace();
		float dim4_data[2] = {-1.5,1.5};
		dataset_4D_dim4.write(dim4_data,H5::PredType::NATIVE_FLOAT,dset_4D_dimSpace,dim4_4D_fspace);
		
		//set up str data space/type and di1 str buffer
		H5::DataSpace str_name_ds(H5S_SCALAR);
		H5::StrType strdatatype(H5::PredType::C_S1,256);

		const H5std_string dataset_4D_dim4_name_str("qx");
		H5::Attribute dataset_4D_dim4_name = dataset_4D_dim4.createAttribute("name",strdatatype,str_name_ds);
		dataset_4D_dim4_name.write(strdatatype, dataset_4D_dim4_name_str);


		const H5std_string dataset_4D_dim4_units_str("[n_m^-1]");
		H5::Attribute dataset_4D_dim4_units = dataset_4D_dim4.createAttribute("units",strdatatype,str_name_ds);
		dataset_4D_dim4_units.write(strdatatype, dataset_4D_dim4_units_str);
	}

	//initialize 3D data set ala virtual detector
	H5::Group threeDim(umbrella.createGroup("virtual_detector"));
	hsize_t dims2[3] = {2,2,4};
	H5::DataSpace threeDim_mspace(3,dims2);

	H5::DataSet VD = threeDim.createDataSet("data",H5::PredType::NATIVE_FLOAT,threeDim_mspace);
	
	//writing dummy virtual detector data
	{
		H5::DataSpace fspace = VD.getSpace();

		float data[16];
		for(auto i = 0; i < 16; i++) data[i] = 0.15*i;

		VD.write(data,H5::PredType::NATIVE_FLOAT,threeDim_mspace,fspace);
	}
	
	//writing virtual detector dimensions
	//dim1	
	{
		hsize_t dim_attr_dims[1] = {2};
		H5::DataSpace vd_dimSpace(1,dim_attr_dims);
		H5::DataSet vd_dim1 = threeDim.createDataSet("dim1",H5::PredType::NATIVE_FLOAT,vd_dimSpace);

		H5::DataSpace vd_dim1_fspace = vd_dim1.getSpace();
		float dim1_data[2] = {-1.5,1.5};
		vd_dim1.write(dim1_data,H5::PredType::NATIVE_FLOAT,vd_dimSpace,vd_dim1_fspace);

		//set up str data space/type and di1 str buffer
		H5::DataSpace str_name_ds(H5S_SCALAR);
		H5::StrType strdatatype(H5::PredType::C_S1,256);

		const H5std_string vd_dim1_name_str("ay");
		H5::Attribute vd_dim1_name = vd_dim1.createAttribute("name",strdatatype,str_name_ds);
		vd_dim1_name.write(strdatatype, vd_dim1_name_str);


		const H5std_string vd_dim1_units_str("[n_m]");
		H5::Attribute vd_dim1_units = vd_dim1.createAttribute("units",strdatatype,str_name_ds);
		vd_dim1_units.write(strdatatype, vd_dim1_units_str);
	}

	//dim2
	{
		hsize_t dim_attr_dims[1] = {2};
		H5::DataSpace vd_dimSpace(1,dim_attr_dims);
		H5::DataSet vd_dim2 = threeDim.createDataSet("dim2",H5::PredType::NATIVE_FLOAT,vd_dimSpace);

		H5::DataSpace vd_dim2_fspace = vd_dim2.getSpace();
		float dim2_data[2] = {-1.5,1.5};
		vd_dim2.write(dim2_data,H5::PredType::NATIVE_FLOAT,vd_dimSpace,vd_dim2_fspace);

		//set up str data space/type and di1 str buffer
		H5::DataSpace str_name_ds(H5S_SCALAR);
		H5::StrType strdatatype(H5::PredType::C_S1,256);

		const H5std_string vd_dim2_name_str("ax");
		H5::Attribute vd_dim2_name = vd_dim2.createAttribute("name",strdatatype,str_name_ds);
		vd_dim2_name.write(strdatatype, vd_dim2_name_str);


		const H5std_string vd_dim2_units_str("[n_m]");
		H5::Attribute vd_dim2_units = vd_dim2.createAttribute("units",strdatatype,str_name_ds);
		vd_dim2_units.write(strdatatype, vd_dim2_units_str);
	}

	//dim3
	{
		hsize_t dim_attr_dims[1] = {4};
		H5::DataSpace vd_dimSpace(1,dim_attr_dims);
		H5::DataSet vd_dim3 = threeDim.createDataSet("dim3",H5::PredType::NATIVE_FLOAT,vd_dimSpace);

		H5::DataSpace vd_dim3_fspace = vd_dim3.getSpace();
		float dim3_data[4] = {0,2,4,6};
		vd_dim3.write(dim3_data,H5::PredType::NATIVE_FLOAT,vd_dimSpace,vd_dim3_fspace);

		//set up str data space/type and di1 str buffer
		H5::DataSpace str_name_ds(H5S_SCALAR);
		H5::StrType strdatatype(H5::PredType::C_S1,256);

		const H5std_string vd_dim3_name_str("bins");
		H5::Attribute vd_dim3_name = vd_dim3.createAttribute("name",strdatatype,str_name_ds);
		vd_dim3_name.write(strdatatype, vd_dim3_name_str);


		const H5std_string vd_dim3_units_str("[d_mrad]");
		H5::Attribute vd_dim3_units = vd_dim3.createAttribute("units",strdatatype,str_name_ds);
		vd_dim3_units.write(strdatatype, vd_dim3_units_str);
	}

	//initialize 2D data set ala HAADF
	H5::Group haadf(umbrella.createGroup("haadf"));
	hsize_t dims3[2] = {5,5};
	H5::DataSpace haadf_mspace(2,dims3);

	H5::DataSet haadf_data = haadf.createDataSet("data",H5::PredType::NATIVE_FLOAT,haadf_mspace);

	//writing dummy haadf data
	{
		H5::DataSpace fspace = haadf_data.getSpace();

		float data[5][5] = {{0,0.25,0,0.25,0},{0.25,0.5,0.35,0.5,0.25},{0,0.35,0.15,0.35,0},{0.25,0.5,0.35,0.5,0.25},{0,0.25,0,0.25,0}};

		haadf_data.write(data,H5::PredType::NATIVE_FLOAT,haadf_mspace,fspace);
	}

	//writing haadf dimensions
	//dim1
	{
		hsize_t dim_attr_dims[1] = {4};
		H5::DataSpace haadf_dimSpace(1,dim_attr_dims);
		H5::DataSet haadf_dim1_dataset = haadf.createDataSet("dim1",H5::PredType::NATIVE_FLOAT,haadf_dimSpace);

		H5::DataSpace haadf_dim1_fspace = haadf_dim1_dataset.getSpace();
		float dim1_data[4] = {0.0,2.5,5,7.5};
		haadf_dim1_dataset.write(dim1_data,H5::PredType::NATIVE_FLOAT,haadf_dimSpace,haadf_dim1_fspace);

		//write attributes for the dimension
		//set up str data space/type and di1 str buffer
		H5::DataSpace str_name_ds(H5S_SCALAR);
		H5::StrType strdatatype(H5::PredType::C_S1,256);

		const H5std_string haadf_dim1_name_str("ay");
		H5::Attribute haadf_dim1_name = haadf_dim1_dataset.createAttribute("name",strdatatype,str_name_ds);
		haadf_dim1_name.write(strdatatype, haadf_dim1_name_str);


		const H5std_string haadf_dim1_units_str("[n_m]");
		H5::Attribute haadf_dim1_units = haadf_dim1_dataset.createAttribute("units",strdatatype,str_name_ds);
		haadf_dim1_units.write(strdatatype, haadf_dim1_units_str);
	}
	//dim2
	{
		hsize_t dim_attr_dims[1] = {4};
		H5::DataSpace haadf_dimSpace(1,dim_attr_dims);
		H5::DataSet haadf_dim2_dataset = haadf.createDataSet("dim2",H5::PredType::NATIVE_FLOAT,haadf_dimSpace);

		H5::DataSpace haadf_dim2_fspace = haadf_dim2_dataset.getSpace();
		float dim2_data[4] = {0.0,2.5,5,7.5};
		haadf_dim2_dataset.write(dim2_data,H5::PredType::NATIVE_FLOAT,haadf_dimSpace,haadf_dim2_fspace);

		//write attributes for the dimension
		//set up str data space/type and di1 str buffer
		H5::DataSpace str_name_ds(H5S_SCALAR);
		H5::StrType strdatatype(H5::PredType::C_S1,256);

		const H5std_string haadf_dim2_name_str("ax");
		H5::Attribute haadf_dim2_name = haadf_dim2_dataset.createAttribute("name",strdatatype,str_name_ds);
		haadf_dim2_name.write(strdatatype, haadf_dim2_name_str);


		const H5std_string haadf_dim2_units_str("[n_m]");
		H5::Attribute haadf_dim2_units = haadf_dim2_dataset.createAttribute("units",strdatatype,str_name_ds);
		haadf_dim2_units.write(strdatatype, haadf_dim2_units_str);
	}

	//initialize 3D data set ala DPC CoM
	//using sub groups do save DPC_kx and DPC_ky
	H5::Group dpc_com(umbrella.createGroup("dpc_com"));

	H5::Group dpc_com_kx(dpc_com.createGroup("dpc_com_kx"));
	H5::Group dpc_com_ky(dpc_com.createGroup("dpc_com_ky"));

	hsize_t dims4[2] = {4,4};
	H5::DataSpace dpc_com_mspace(2,dims4);

	H5::DataSet dpc_com_kx_data = dpc_com_kx.createDataSet("data",H5::PredType::NATIVE_FLOAT,dpc_com_mspace);
	H5::DataSet dpc_com_ky_data = dpc_com_ky.createDataSet("data",H5::PredType::NATIVE_FLOAT,dpc_com_mspace);

	//writing dummy dpc com data
	{
		H5::DataSpace fspace = dpc_com_kx_data.getSpace();
		H5::DataSpace fspace2 = dpc_com_ky_data.getSpace();

		float data[16];
		for(auto i = 0; i < 16; i++) data[i] = 0.15*i;

		float data2[16];
		for(auto i = 0; i < 16; i++) data2[i] = 0.15*(15-i);

		dpc_com_kx_data.write(data,H5::PredType::NATIVE_FLOAT,dpc_com_mspace,fspace);
		dpc_com_ky_data.write(data2,H5::PredType::NATIVE_FLOAT,dpc_com_mspace,fspace2);

	}
	//writing dpc com dimensions

	//dim1
	{	
		//kx
		{
			hsize_t dim_attr_dims[1] = {4};
			H5::DataSpace dpc_com_kx_dimSpace(1,dim_attr_dims);
			H5::DataSet dpc_com_kx_dim1_dataset = dpc_com_kx.createDataSet("dim1",H5::PredType::NATIVE_FLOAT,dpc_com_kx_dimSpace);

			H5::DataSpace dpc_com_kx_dim1_fspace = dpc_com_kx_dim1_dataset.getSpace();
			float dim1_data[4] = {0.0,2.5,5,7.5};
			dpc_com_kx_dim1_dataset.write(dim1_data,H5::PredType::NATIVE_FLOAT,dpc_com_kx_dimSpace,dpc_com_kx_dim1_fspace);

			//write attributes for the dimension
			//set up str data space/type and di1 str buffer
			H5::DataSpace str_name_ds(H5S_SCALAR);
			H5::StrType strdatatype(H5::PredType::C_S1,256);

			const H5std_string dpc_com_kx_dim1_name_str("ay");
			H5::Attribute dpc_com_kx_dim1_name = dpc_com_kx_dim1_dataset.createAttribute("name",strdatatype,str_name_ds);
			dpc_com_kx_dim1_name.write(strdatatype, dpc_com_kx_dim1_name_str);


			const H5std_string dpc_com_kx_dim1_units_str("[n_m]");
			H5::Attribute dpc_com_kx_dim1_units = dpc_com_kx_dim1_dataset.createAttribute("units",strdatatype,str_name_ds);
			dpc_com_kx_dim1_units.write(strdatatype, dpc_com_kx_dim1_units_str);
		}

		//ky
		{
			hsize_t dim_attr_dims[1] = {4};
			H5::DataSpace dpc_com_ky_dimSpace(1,dim_attr_dims);
			H5::DataSet dpc_com_ky_dim1_dataset = dpc_com_ky.createDataSet("dim1",H5::PredType::NATIVE_FLOAT,dpc_com_ky_dimSpace);

			H5::DataSpace dpc_com_ky_dim1_fspace = dpc_com_ky_dim1_dataset.getSpace();
			float dim1_data[4] = {0.0,2.5,5,7.5};
			dpc_com_ky_dim1_dataset.write(dim1_data,H5::PredType::NATIVE_FLOAT,dpc_com_ky_dimSpace,dpc_com_ky_dim1_fspace);

			//write attributes for the dimension
			//set up str data space/type and di1 str buffer
			H5::DataSpace str_name_ds(H5S_SCALAR);
			H5::StrType strdatatype(H5::PredType::C_S1,256);

			const H5std_string dpc_com_ky_dim1_name_str("ay");
			H5::Attribute dpc_com_ky_dim1_name = dpc_com_ky_dim1_dataset.createAttribute("name",strdatatype,str_name_ds);
			dpc_com_ky_dim1_name.write(strdatatype, dpc_com_ky_dim1_name_str);


			const H5std_string dpc_com_ky_dim1_units_str("[n_m]");
			H5::Attribute dpc_com_ky_dim1_units = dpc_com_ky_dim1_dataset.createAttribute("units",strdatatype,str_name_ds);
			dpc_com_ky_dim1_units.write(strdatatype, dpc_com_ky_dim1_units_str);
		}
	}

	//dim2
	{	
		//kx
		{
			hsize_t dim_attr_dims[1] = {4};
			H5::DataSpace dpc_com_kx_dimSpace(1,dim_attr_dims);
			H5::DataSet dpc_com_kx_dim2_dataset = dpc_com_kx.createDataSet("dim2",H5::PredType::NATIVE_FLOAT,dpc_com_kx_dimSpace);

			H5::DataSpace dpc_com_kx_dim2_fspace = dpc_com_kx_dim2_dataset.getSpace();
			float dim2_data[4] = {0.0,2.5,5,7.5};
			dpc_com_kx_dim2_dataset.write(dim2_data,H5::PredType::NATIVE_FLOAT,dpc_com_kx_dimSpace,dpc_com_kx_dim2_fspace);

			//write attributes for the dimension
			//set up str data space/type and di1 str buffer
			H5::DataSpace str_name_ds(H5S_SCALAR);
			H5::StrType strdatatype(H5::PredType::C_S1,256);

			const H5std_string dpc_com_kx_dim2_name_str("ax");
			H5::Attribute dpc_com_kx_dim2_name = dpc_com_kx_dim2_dataset.createAttribute("name",strdatatype,str_name_ds);
			dpc_com_kx_dim2_name.write(strdatatype, dpc_com_kx_dim2_name_str);


			const H5std_string dpc_com_kx_dim2_units_str("[n_m]");
			H5::Attribute dpc_com_kx_dim2_units = dpc_com_kx_dim2_dataset.createAttribute("units",strdatatype,str_name_ds);
			dpc_com_kx_dim2_units.write(strdatatype, dpc_com_kx_dim2_units_str);
		}

		//ky
		{
			hsize_t dim_attr_dims[1] = {4};
			H5::DataSpace dpc_com_ky_dimSpace(1,dim_attr_dims);
			H5::DataSet dpc_com_ky_dim2_dataset = dpc_com_ky.createDataSet("dim2",H5::PredType::NATIVE_FLOAT,dpc_com_ky_dimSpace);

			H5::DataSpace dpc_com_ky_dim2_fspace = dpc_com_ky_dim2_dataset.getSpace();
			float dim2_data[4] = {0.0,2.5,5,7.5};
			dpc_com_ky_dim2_dataset.write(dim2_data,H5::PredType::NATIVE_FLOAT,dpc_com_ky_dimSpace,dpc_com_ky_dim2_fspace);

			//write attributes for the dimension
			//set up str data space/type and di1 str buffer
			H5::DataSpace str_name_ds(H5S_SCALAR);
			H5::StrType strdatatype(H5::PredType::C_S1,256);

			const H5std_string dpc_com_ky_dim2_name_str("ax");
			H5::Attribute dpc_com_ky_dim2_name = dpc_com_ky_dim2_dataset.createAttribute("name",strdatatype,str_name_ds);
			dpc_com_ky_dim2_name.write(strdatatype, dpc_com_ky_dim2_name_str);


			const H5std_string dpc_com_ky_dim2_units_str("[n_m]");
			H5::Attribute dpc_com_ky_dim2_units = dpc_com_ky_dim2_dataset.createAttribute("units",strdatatype,str_name_ds);
			dpc_com_ky_dim2_units.write(strdatatype, dpc_com_ky_dim2_units_str);
		}
	}

	//write meta data
	//metadata group
	H5::Group metadata(umbrella.createGroup("metadata"));
	
	//top level groups
	H5::Group parameters(metadata.createGroup("parameters"));
	H5::Group sample(metadata.createGroup("sample"));
	H5::Group user(metadata.createGroup("user"));
	H5::Group comments(metadata.createGroup("comments"));


	return 0;
}

