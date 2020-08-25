#pragma once
#ifndef yxDESH
#define yxDESH
#include <string>
//support CBC ECB mode,you can  padding  PKCS5 or NOPKCS by yuzj 2010 5 10
#define NOPKCS 0 //Ĭ��
#define PKCS5 1


#define ECB_MODE 0 //Ĭ��
#define CBC_MODE 1

class yxDES
{
public:
	static std::string Encrypt(const std::string &src, const char* key, int iMode = ECB_MODE,int iPKCS = PKCS5);
	static std::string Decrypt(const std::string &src, const char* key, int iMode = ECB_MODE,int iPKCS = PKCS5);

private:
	//�๹�캯��
	yxDES(int length=8192); 

	//����������
	~yxDES(); 

	//����:���üӽ��ܺ����ģʽ������û�������Ĭ��ģʽ����0
	//����:����
	//���:�������������int m_iMode��int m_iPkcs
	void SetModeAndPKCS(int iMode = 0,int iPKCS = 0);

	//����:����IV,Ĭ��Ϊ{0,0,0,0,0,0,0,0}
	//����:8λ�ַ���
	//���:�������������char szvi[8]��char szviRev[8]
	void SetIV(char* srcBytes);

	//����:����16��28λ��key
	//����:Դ8λ���ַ���(key),���key�����0-1
	//���:����������private CreateSubKey���������char SubKeys[keyN][16][48]
	void InitializeKey(const char* srcBytes,unsigned int keyN);

	//����:����8λ�ַ���
	//����:8λ�ַ���,ʹ��Key�����0-1
	//���:���������ܺ��������private szCiphertext[16]
	//      �û�ͨ������Ciphertext�õ�
	void EncryptData(char* _srcBytes,unsigned int keyN);

	//����:����16λʮ�������ַ���
	//����:16λʮ�������ַ���,ʹ��Key�����0-1
	//���:���������ܺ��������private szPlaintext[8]
	//      �û�ͨ������Plaintext�õ�
	void DecryptData(char* _srcBytes,unsigned int keyN);

	//����:�������ⳤ���ַ���
	//����:���ⳤ���ַ���,����,ʹ��Key�����0-1
	//���:���������ܺ��������private szFCiphertextAnyLength[8192]
	//      �û�ͨ������CiphertextAnyLength�õ�
	void EncryptAnyLength(char* _srcBytes,unsigned int _bytesLength,unsigned int keyN);

	//����:�������ⳤ��ʮ�������ַ���
	//����:���ⳤ���ַ���,����,ʹ��Key�����0-1
	//���:���������ܺ��������private szFPlaintextAnyLength[8192]
	//      �û�ͨ������PlaintextAnyLength�õ�
	void DecryptAnyLength(char* _srcBytes,unsigned int _bytesLength, unsigned int keyN);

	//����:Bytes��Bits��ת��,
	//����:���任�ַ���,���������Ż�����ָ��,Bits��������С
	void Bytes2Bits(const char *srcBytes, char* dstBits, unsigned int sizeBits);

	//����:Bits��Bytes��ת��,
	//����:���任�ַ���,���������Ż�����ָ��,Bits��������С
	void Bits2Bytes(char *dstBytes, char* srcBits, unsigned int sizeBits);

	//����:Int��Bits��ת��,
	//����:���任�ַ���,���������Ż�����ָ��
	void Int2Bits(unsigned int srcByte, char* dstBits);

	//����:Bits��Hex��ת��
	//����:���任�ַ���,���������Ż�����ָ��,Bits��������С
	void Bits2Hex(char *dstHex, char* srcBits, unsigned int sizeBits);

	//����:Bits��Hex��ת��
	//����:���任�ַ���,���������Ż�����ָ��,Bits��������С
	void Hex2Bits(char *srcHex, char* dstBits, unsigned int sizeBits);

	//szCiphertextInBinary��get����
	char* GetCiphertextInBinary();

	//szCiphertextInHex��get����
	char* GetCiphertextInHex();

	//Ciphertext��get����
	char* GetCiphertextInBytes();

	//Plaintext��get����
	char* GetPlaintext();

	//CiphertextAnyLength��get����
	char* GetCiphertextAnyLength();

	//PlaintextAnyLength��get����
	char* GetPlaintextAnyLength();

	//�ַ���ת16���������ı�
	void ConvertCiphertext2Hex(char *szPlainInBytes);

	//16��������ת�ַ���
	int ConvertHex2Ciphertext(const char *szCipherInBytes);

	//CiphertextData����
	char* GetCiphertextData();

	//hexCiphertextAnyLength����
	char* GetHexCipherAnyLengthData();



private:
	int  m_iLength;
	char szSubKeys[2][16][48];//����2��16��48λ��Կ,��2������3DES
	char szCiphertextRaw[64]; //�������������(64��Bits) int 0,1
	char szPlaintextRaw[64]; //�������������(64��Bits) int 0,1
	char szCiphertextInBytes[8];//����8λ����
	char szPlaintextInBytes[8];//����8λ�����ַ���

	char szCiphertextInBinary[65]; //�������������(64��Bits) char '0','1',���һλ��'\0'
	char szCiphertextInHex[17]; //����ʮ����������,���һλ��'\0'
	char szPlaintext[9];//����8λ�����ַ���,���һλ��'\0'

	char* szFCiphertextAnyLength;//���ⳤ������
	char* szFPlaintextAnyLength;//���ⳤ�������ַ���

	char* szCiphertextData;
	char* hexCiphertextAnyLength;

	char sziv[8];//����IV
	char szivRev[8];//����IV	

	int m_iMode;//�ӽ���ģʽ
	int m_iPkcs;//���ģʽ

	int data_base_length_;//���ڱ������Ҫ���ַ����泤��



	//����:��������Կ
	//����:����PC1�任��56λ�������ַ���,���ɵ�szSubKeys���0-1
	//���:��������char szSubKeys[16][48]
	void CreateSubKey(char* sz_56key,unsigned int keyN);

	//����:DES�е�F����,
	//����:��32λ,��32λ,key���(0-15),ʹ�õ�szSubKeys���0-1
	//���:���ڱ任����32λ
	void FunctionF(char* sz_Li,char* sz_Ri,unsigned int iKey,unsigned int keyN);

	//����:IP�任
	//����:�������ַ���,����������ָ��
	//���:�����ı�ڶ�������������
	void InitialPermuteData(char* _src,char* _dst);

	//����:����32λ������չλ48λ,
	//����:ԭ32λ�ַ���,��չ�������ָ��
	//���:�����ı�ڶ�������������
	void ExpansionR(char* _src,char* _dst);

	//����:�����,
	//����:�����Ĳ����ַ���1,�ַ���2,����������,����������ָ��
	//���: �����ı���ĸ�����������
	void XOR(char* szParam1,char* szParam2, unsigned int uiParamLength, char* szReturnValueBuffer);

	//����:S-BOX , ����ѹ��,
	//����:48λ�������ַ���,
	//���:���ؽ��:32λ�ַ���
	void CompressFuncS(char* _src48, char* _dst32);

	//����:IP��任,
	//����:���任�ַ���,����������ָ��
	//���:�����ı�ڶ�������������
	void PermutationP(char* _src,char* _dst);

};

#endif
 