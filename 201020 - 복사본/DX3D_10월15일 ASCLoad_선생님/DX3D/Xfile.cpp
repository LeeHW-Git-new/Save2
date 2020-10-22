#include "stdafx.h"
#include "Xfile.h"


Xfile::Xfile()
{
}


Xfile::~Xfile()
{
}

void Xfile::Setup()
{
	HRESULT hr = 0;
	hr = D3DXLoadMeshFromX(L"Zealot/zealot.X", D3DXMESH_MANAGED, g_pD3DDevice, &adjBuffer, &mtrlBuffer, 0, &numMtrls, &Mesh);

	if (FAILED(hr))
	{
		::MessageBox(0, L"D3DXLoadMeshFromX() - FAILED", 0, 0);
		return;
	}

	if (mtrlBuffer != 0 && numMtrls != 0)
	{
		D3DXMATERIAL* mtrls = (D3DXMATERIAL*)mtrlBuffer->GetBufferPointer();

		for (int i = 0; i < numMtrls; i++)
		{
			mtrls[i].MatD3D.Ambient = mtrls[i].MatD3D.Diffuse;

			Mtrls.push_back(mtrls[i].MatD3D);

			string filename = string("Zealot") + "/" + mtrls[i].pTextureFilename;

			if (mtrls[i].pTextureFilename != 0)
			{
				IDirect3DTexture9* tex = 0;
				D3DXCreateTextureFromFileA(g_pD3DDevice, filename.c_str(), &tex);

				Textures.push_back(tex);
			}
			else
			{
				Textures.push_back(0);
			}
		}
	}
	SafeRelease(mtrlBuffer);
}

void Xfile::Render()
{
	if (g_pD3DDevice)
	{
		static float y = 0.0f;
		D3DXMATRIX yRot , scale;
		D3DXMatrixRotationY(&yRot, y);
		y += 0.01f;

		if (y >= 6.28f)
			y = 0.0f;

		D3DXMatrixScaling(&scale, 5.0f, 5.0f, 5.0f);
		D3DXMATRIX World = scale * yRot ;
		g_pD3DDevice->SetTransform(D3DTS_WORLD, &World);


		for (int i = 0; i < Mtrls.size(); i++)
		{
			g_pD3DDevice->SetMaterial(&Mtrls[i]);
			g_pD3DDevice->SetTexture(0, Textures[i]);
			Mesh->DrawSubset(i);
		}
	}
}
