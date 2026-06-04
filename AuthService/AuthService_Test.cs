using System;
using Xunit;
using Lab3;

namespace Lab3.Tests
{
    public class AuthServiceTests
    {
        private readonly AuthService _authService;

        public AuthServiceTests()
        {
            // Підготовка загального оточення для кожного тесту
            _authService = new AuthService();
        }

        #region Тести методу Register

        [Fact(DisplayName = "Register: Успішна реєстрація з коректними даними")]
        public void Register_ValidData_ReturnsUser()
        {
            // Техніка: EP (Класи еквівалентності), Позитивний тест
            
            // Arrange
            string email = "test@example.com";
            string password = "strongPassword123"; 

            // Act
            User result = _authService.Register(email, password);

            // Assert
            Assert.NotNull(result);
            Assert.Equal(email, result.Email);
            Assert.False(string.IsNullOrEmpty(result.PasswordHash));
        }

        [Fact(DisplayName = "Register: Помилка при спробі реєстрації дубліката Email")]
        public void Register_DuplicateEmail_ThrowsInvalidOperationException()
        {
            // Техніка: EP (Класи еквівалентності), Негативний тест
            
            // Arrange
            string email = "duplicate@example.com";
            _authService.Register(email, "password123");

            // Act & Assert
            Assert.Throws<InvalidOperationException>(() => _authService.Register(email, "newPassword123"));
        }

        [Fact(DisplayName = "Register: Помилка, якщо довжина пароля рівно 5 символів")]
        public void Register_PasswordExactly5Chars_ThrowsArgumentException()
        {
            // Техніка: BVA (Граничні значення), Негативний тест
            
            // Arrange
            string email = "boundary@example.com";
            string shortPassword = "12345"; // Границя: 5 символів (менше дозволених 6)

            // Act & Assert
            Assert.Throws<ArgumentException>(() => _authService.Register(email, shortPassword));
        }

        #endregion

        #region Тести методу Authenticate

        [Fact(DisplayName = "Authenticate: Успішна авторизація з вірними обліковими даними")]
        public void Authenticate_CorrectCredentials_ReturnsAuthToken()
        {
            // Техніка: EP (Класи еквівалентності), Позитивний тест
            
            // Arrange
            string email = "auth@example.com";
            string password = "secure_password";
            _authService.Register(email, password);

            // Act
            AuthToken token = _authService.Authenticate(email, password);

            // Assert
            Assert.NotNull(token);
            Assert.False(string.IsNullOrEmpty(token.Token));
            Assert.True(token.ExpiresAt > DateTime.UtcNow);
        }

        [Fact(DisplayName = "Authenticate: Помилка автентифікації неіснуючого користувача")]
        public void Authenticate_UserDoesNotExist_ThrowsInvalidOperationException()
        {
            // Техніка: EP (Класи еквівалентності), Негативний тест
            
            // Arrange
            string nonExistentEmail = "fake@example.com";

            // Act & Assert
            Assert.Throws<InvalidOperationException>(() => _authService.Authenticate(nonExistentEmail, "anyPassword"));
        }

        [Fact(DisplayName = "Authenticate: Помилка автентифікації з неправильним паролем")]
        public void Authenticate_WrongPassword_ThrowsUnauthorizedAccessException()
        {
            // Техніка: EP (Класи еквівалентності), Негативний тест
            
            // Arrange
            string email = "user@example.com";
            _authService.Register(email, "correctPassword");

            // Act & Assert
            Assert.Throws<UnauthorizedAccessException>(() => _authService.Authenticate(email, "wrongPassword"));
        }

        #endregion

        #region Тести методу ValidateToken

        [Fact(DisplayName = "ValidateToken: Токен дійсний, якщо час його життя в майбутньому")]
        public void ValidateToken_ValidToken_ReturnsTrue()
        {
            // Техніка: BVA (Граничні значення), Позитивний тест
            
            // Arrange
            string email = "token@example.com";
            _authService.Register(email, "password123");
            AuthToken activeToken = _authService.Authenticate(email, "password123");

            // Act
            bool isValid = _authService.ValidateToken(activeToken);

            // Assert
            Assert.True(isValid);
        }

        [Fact(DisplayName = "ValidateToken: Токен недійсний, якщо час його життя вже минув")]
        public void ValidateToken_ExpiredToken_ReturnsFalse()
        {
            // Техніка: BVA (Граничні значення), Негативний тест
            
            // Arrange
            var expiredToken = new AuthToken
            {
                Token = Guid.NewGuid().ToString(),
                ExpiresAt = DateTime.UtcNow.AddMinutes(-5) // Границя зміщена в минуле
            };

            // Act
            bool isValid = _authService.ValidateToken(expiredToken);

            // Assert
            Assert.False(isValid);
        }

        #endregion

        #region Тести методу HashPassword

        [Fact(DisplayName = "HashPassword: Успішне хэшування коректного рядка пароля")]
        public void HashPassword_ValidString_ReturnsSha256String()
        {
            // Техніка: EP (Класи еквівалентності), Позитивний тест
            
            // Arrange
            string password = "myPassword125";

            // Act
            string hash = _authService.HashPassword(password);

            // Assert
            Assert.NotNull(hash);
            Assert.Equal(64, hash.Length); // Довжина SHA-256 завжди 64 символи
        }

        [Fact(DisplayName = "HashPassword: Повернення порожнього рядка при обробці порожнього пароля")]
        public void HashPassword_EmptyString_ReturnsEmptyString()
        {
            // Техніка: BVA (Граничні значення), Позитивний тест / Крайовий випадок
            
            // Arrange
            string emptyPassword = "";

            // Act
            string hash = _authService.HashPassword(emptyPassword);

            // Assert
            Assert.Equal(string.Empty, hash);
        }

        #endregion
    }
}