using System;
using System.Collections.Generic;
using System.Security.Cryptography;
using System.Text;

namespace Lab3
{
    // Мінімальна реалізація інших класів для демонстрації логіки AuthService
    public class AuthToken
    {
        public string? Token { get; set; }
        public DateTime ExpiresAt { get; set; }
    }

    public class User
    {
        public string? Email { get; set; }
        public string? PasswordHash { get; set; }
    }

    /// <summary>
    /// Реалізація програмного модуля AuthService
    /// </summary>
    public class AuthService
    {
        private readonly List<User> _usersDb = new List<User>();
        private readonly Dictionary<string, AuthToken> _activeTokens = new Dictionary<string, AuthToken>();

        /// <summary>
        /// Метод 1: Аутентифікація
        /// </summary>
        public AuthToken Authenticate(string email, string pwd)
        {
            if (string.IsNullOrWhiteSpace(email) || string.IsNullOrWhiteSpace(pwd))
            {
                throw new ArgumentException("Email and password cannot be empty.");
            }

            // Пошук користувача пошук без урахування регістру
            User user = _usersDb.Find(u => u.Email.Equals(email, StringComparison.OrdinalIgnoreCase));
            if (user == null)
            {
                throw new InvalidOperationException("User not found.");
            }

            string incomingHash = HashPassword(pwd);
            if (user.PasswordHash != incomingHash)
            {
                throw new UnauthorizedAccessException("Invalid credentials.");
            }

            var token = new AuthToken
            {
                Token = Guid.NewGuid().ToString(),
                ExpiresAt = DateTime.UtcNow.AddHours(2)
            };

            _activeTokens[token.Token] = token;
            return token;
        }

        /// <summary>
        /// Метод 2: Реєстрація
        /// </summary>
        public User Register(string email, string pwd)
        {
            if (string.IsNullOrWhiteSpace(email) || string.IsNullOrWhiteSpace(pwd) || pwd.Length < 6)
            {
                throw new ArgumentException("Invalid email or password is too short (min 6 characters).");
            }

            // перевірка, не зайнятий ли email
            bool userExists = _usersDb.Exists(u => u.Email.Equals(email, StringComparison.OrdinalIgnoreCase));
            if (userExists)
            {
                throw new InvalidOperationException("User with this email already exists.");
            }

            var newUser = new User
            {
                Email = email,
                PasswordHash = HashPassword(pwd)
            };

            _usersDb.Add(newUser);
            return newUser;
        }

        public bool ValidateToken(AuthToken token)
        {
            if (token == null || string.IsNullOrEmpty(token.Token))
            {
                return false;
            }

            if (_activeTokens.TryGetValue(token.Token, out var foundToken))
            {
                if (foundToken.ExpiresAt > DateTime.UtcNow)
                {
                    return true;
                }
                else
                {
                    _activeTokens.Remove(token.Token);
                }
            }

            return false;
        }

        public string HashPassword(string pwd)
        {
            if (string.IsNullOrEmpty(pwd)) return string.Empty;

            using (SHA256 sha256 = SHA256.Create())
            {
                byte[] bytes = sha256.ComputeHash(Encoding.UTF8.GetBytes(pwd));
                StringBuilder builder = new StringBuilder();
                
                for (int i = 0; i < bytes.Length; i++)
                {
                    builder.Append(bytes[i].ToString("x2"));
                }
                return builder.ToString();
            }
        }
    }
}