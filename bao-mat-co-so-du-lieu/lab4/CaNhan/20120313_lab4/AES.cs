using System;
using System.Security.Cryptography;
using System.Text;

namespace _20120313_lab4
{
    internal class AES
    {
        public static byte[] Encrypt(string plainText, string password)
        {
            byte[] iv = new byte[16];
            byte[] key = new Rfc2898DeriveBytes(password, iv, 1000).GetBytes(32);

            byte[] encrypted;

            using (Aes aes = Aes.Create())
            {
                aes.Key = key;
                aes.IV = iv;
                aes.Padding = PaddingMode.PKCS7;
                aes.Mode = CipherMode.CBC;
                ICryptoTransform encryptor = aes.CreateEncryptor(aes.Key, aes.IV);

                using (System.IO.MemoryStream ms = new System.IO.MemoryStream())
                {
                    using (CryptoStream cs = new CryptoStream(ms, encryptor, CryptoStreamMode.Write))
                    {
                        using (System.IO.StreamWriter sw = new System.IO.StreamWriter(cs))
                        {
                            sw.Write(plainText);
                        }
                        encrypted = ms.ToArray();
                    }
                }
            }

            return encrypted;
        }
        public static string Decrypt(byte[] cipherBytes, string password)
        {
            byte[] iv = new byte[16];
            byte[] key = new Rfc2898DeriveBytes(password, iv, 1000).GetBytes(32);

            string plainText = null;
            using (Aes aes = Aes.Create())
            {
                aes.Key = key;
                aes.IV = iv;
                aes.Padding = PaddingMode.PKCS7;
                aes.Mode = CipherMode.CBC;
                ICryptoTransform decryptor = aes.CreateDecryptor(aes.Key, aes.IV);

                using (System.IO.MemoryStream ms = new System.IO.MemoryStream(cipherBytes))
                {
                    using (CryptoStream cs = new CryptoStream(ms, decryptor, CryptoStreamMode.Read))
                    {
                        using (System.IO.StreamReader sr = new System.IO.StreamReader(cs))
                        {
                            plainText = sr.ReadToEnd();
                        }
                    }
                }
            }

            return plainText;
        }
    }
}

